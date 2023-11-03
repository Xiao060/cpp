// 头文件引入
// 1. 自定义头文件
// 2. C 标准库头文件
// 3. C ++ 标准库头文件
// 4. 第三方库头文件

#include <csignal>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <string>


// 用于阻塞主线程
#include <workflow/HttpMessage.h>
#include <workflow/WFFacilities.h>
// 用于创建子任务
#include <workflow/WFTaskFactory.h>
// 管理任务 (启动...)
#include <workflow/WFTask.h>
// 获取 首部字段
#include <workflow/HttpUtil.h>


using std::cin;
using std::cout;
using std::endl;
using std::string;


// 用来阻塞主进程, 使主进程等待子进程执行完任务, 类似于 pthread_join
// 参数为 待执行的任务数量
static WFFacilities::WaitGroup waitGroup(1);

// 此处 搭配 注册信号使用, 当发送信号时, 任务数量 -1
// 注册信号使用, 即信号的递送行为
void handler(int signum) {
    // 任务数量 -1
    waitGroup.done();
}


// Http 子任务需要绑定 注册回调函数
void httpCallback(WFHttpTask* httpTask) {

    // 获取 连接状态 与 错误码, 并判断
    int state = httpTask->get_state();
    int error = httpTask->get_error();

    switch (state) {
    case WFT_STATE_SYS_ERROR:
        cout << "SYS ERROR: " << strerror(error) << endl;
        return;
    case WFT_STATE_DNS_ERROR:
        cout << "DNS ERROR: " << gai_strerror(error) << endl;
        return;
    }

    if (state != WFT_STATE_SUCCESS) {
        cout << "ERROR: " << strerror(error) << endl;
        return;
    }

    cout << "success" << endl;
    cout << "\n*********************************************\n\n";


    // 获取 默认的请求报文
    // 获取 请求报文的起始行
    protocol::HttpRequest* req = httpTask->get_req();
    const char* method = req->get_method();
    const char* uri = req->get_request_uri();
    const char* reqVersion = req->get_http_version();
    cout << method << " " << uri << " " << reqVersion << endl;
    // 获取 首部字段
    protocol::HttpHeaderCursor reqCursor(req);
    string key1, value1;
    while (reqCursor.next(key1, value1)) {
        cout << key1 << ": " << value1 << endl;
    }
    // 获取 请求报文报文体
    // const void* reqBody = nullptr;
    // size_t reqSize = 0;
    // req->get_outputbody_blocks(&reqBody, &reqSize, 100);
    void* reqBody = new char[30];
    size_t reqSize = 30;
    req->get_output_body_merged(reqBody, &reqSize);
    cout << endl << (char*) reqBody << endl;


    cout << "\n*********************************************\n\n";


    // 获取 响应报文
    // 获取 响应报文的起始行
    protocol::HttpResponse* resp = httpTask->get_resp();
    const char* respVersion = resp->get_http_version();
    const char* statusCode = resp->get_status_code();
    const char* reasonPhrase = resp->get_reason_phrase();
    cout << respVersion << " " << statusCode << " " << reasonPhrase << endl;
    // 获取 响应报文的首部字段
    protocol::HttpHeaderCursor respCursor(resp);
    string key2, value2;
    while (respCursor.next(key2, value2)) {
        cout << key2 << ": " << value2 << endl;
    }
    // 获取 响应报文的报文体
    const void* respBody = nullptr;
    size_t respSize = 0;
    resp->get_parsed_body(&respBody, &respSize);
    cout << endl << (char*) respBody << endl;

    // waitGroup.done();
}



int main(int argc, char* argv[]) {

    signal(SIGINT, handler);

    // 1. 将业务拆分成不同的子任务
    // start()后 每个子任务 先执行基本工作, 然后执行 回调函数
    // 基本工作 由框架完成
    // workflow 中子任务需要借助 WFTaskFactory 来完成 
    WFHttpTask* httpTask = WFTaskFactory::create_http_task("http://www.baidu.com", 
                                                            0,
                                                            0,
                                                            httpCallback);

    // 2. 可以在 start 前修改基本任务的 属性
    protocol::HttpRequest* req = httpTask->get_req();
    req->set_method("POST");
    req->add_header_pair("Content-Type", "text/plain");
    char reqBody[] = "Hello, Server";
    req->append_output_body(reqBody, strlen(reqBody));


    httpTask->start(); 

    // 阻塞, 等待任务全部执行完毕 再继续向下执行
    waitGroup.wait();
    return 0;
}




