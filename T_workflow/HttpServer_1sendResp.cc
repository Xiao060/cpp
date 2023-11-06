// Http 服务器
// 发送响应报文

#include <csignal>
#include <iostream>

// 用于阻塞 主线程
#include <string>
#include <unistd.h>
#include <workflow/HttpMessage.h>
#include <workflow/WFFacilities.h>
// 用于创建 http 服务器
#include <workflow/WFGlobal.h>
#include <workflow/WFHttpServer.h>
// 用于创建 任务
#include <workflow/WFTaskFactory.h>
#include <workflow/WFTask.h>
// 用于获取 http 首部字段
#include <workflow/HttpUtil.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;


static WFFacilities::WaitGroup waitGroup(1);

void handler(int signo) {
    waitGroup.done();
}

void httpCallback(WFHttpTask* httpTask) {
    cout << "httpCallback is running!" << endl;
}

void process(WFHttpTask* httpTask) {
    cout << "process is running!" << endl;

    httpTask->set_callback(httpCallback);

    // 1. 进行 状态检测
    // 获取 状态 及 错误码
    int state = httpTask->get_state();
    int error = httpTask->get_error();
    // 若不成功, 则打印 状态 及 错误码
    // 此处直接调用 WFGlobal::get_error_string() 函数, 避免了使用 switch 的麻烦
    if (state != WFT_STATE_TOREPLY) {
        cout << WFGlobal::get_error_string(state, error) << endl;
        return;
    }

    cout << "\e[93m********************************************************\e[39m" << endl;
    

    // 2. 获取 请求
    protocol::HttpRequest* req = httpTask->get_req();
    // 获取起始行
    string method = req->get_method();
    string uri = req->get_request_uri();
    string version = req->get_http_version();
    cout << method << " " << uri << " " << version << endl;
    // 获取 首部字段
    protocol::HttpHeaderCursor cursor(req);
    string key, value;
    while (cursor.next(key, value)) {
        cout << "\e[93m" << key << "\e[39m: " << value << endl;
    }


    // 2. 获取响应
    protocol::HttpResponse* resp = httpTask->get_resp();
    // 设置 首部字段 / 报文体
    // resp->add_header_pair("Conten-Type", "text/plain");
    // resp->append_output_body("1.hello, client!");
    resp->add_header_pair("Conten-Type", "text/html");
    resp->add_header_pair("Server", "Workflow-Server");
    resp->append_output_body("<html><body>2.hello, client!</body></html>");

    cout << "\e[93m********************************************************\e[39m" << endl;

    waitGroup.done();
}



int main(int argc, char* argv[]) {

    signal(SIGINT, handler);

    // 1. 创建 httpServer, 设置 其 process 函数
    // 启动 http 服务器时会 自动创建 http服务端任务, 并放入序列调度执行
    // 1.1 服务器 先接收 客户端 请求报文
    // 1.2 然后 由 process函数 解析请求/生成响应; 
    // 故 process 参数为 WFHttpTask, 即 httpServer 自动创建的 http服务端任务
    // 1.3 最后再由 服务器 发送请求
    WFHttpServer httpServer(process);


    if (httpServer.start(8888) == 0) {
        cout << "httpServer 启动成功" << endl;
        // 此处 wait() 保证 服务端可以接收到 请求 并 执行process 函数
        // 若没有该函数, 则 客户端来不及发送请求 stop() 检测不到任务执行会直接结束服务端
        waitGroup.wait();
        // stop 会等待 服务端的 http任务执行完成才会结束, 即 基本任务 + process + 回调函数
        httpServer.stop();
    }

    return 0;
}




