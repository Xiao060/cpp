// Http 服务器
// 完成 GET请求 登陆功能
// process 只做 请求解析
// redisTask 完成 信息的验证 并 生成响应报文
// 在回调函数中打印 已发送的响应报文

// 因为 redis 信息验证需要使用 输入的密码
// 设置响应报文 需要 使用 httpTask 的 resp 部分
// 故 需要 将 输入密码/httpTask 设为共享数据
// protocol::HttpResponse 也可以


#include <csignal>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <fcntl.h>

// 用于阻塞 主线程
#include <workflow/WFFacilities.h>
// 用于处理 任务状态 及 错误码
#include <workflow/RedisMessage.h>
#include <workflow/WFGlobal.h>
// 用于创建 http 服务器
#include <workflow/WFHttpServer.h>
// 用于创建 任务
#include <workflow/WFTaskFactory.h>
#include <workflow/WFTask.h>
// 用于获取 http 请求/响应
#include <workflow/HttpMessage.h>
// 用于获取 http 首部字段
#include <workflow/HttpUtil.h>
// 用于获取序列
#include <workflow/Workflow.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

static WFFacilities::WaitGroup waitGroup(2);

void handler(int signo) {
    waitGroup.done();
}


struct SharedData {
    WFHttpTask* httpTask;
    string password;
};


// 注意: http 服务端的任务 执行顺序为 I -> process -> O -> 回调函数, 即
// 1. 接收请求
// 2. 解析请求/生成响应
// 3. 发送报文
// 4. 回调函数
// 故 执行回调函数时 响应报文已发送完毕, 此时设置响应报文无意义, 但是可以打印响应报文
void httpCallback(WFHttpTask* httpTask) {
    cout << "httpCallback is running!" << endl;

    // 打印 响应信息
    // 1. 获取响应报文
    protocol::HttpResponse* resp = httpTask->get_resp();
    // 获取起始行
    string version = resp->get_http_version();
    string code = resp->get_status_code();
    string reason = resp->get_reason_phrase();
    cout << version << " " << code << " " << reason << endl;
    // 获取首部字段
    protocol::HttpHeaderCursor cursor(resp);
    string key, value;
    while (cursor.next(key, value)) {
        cout << "\e[93m" << key << "\e[39m: " << value << endl;
    }
    // 获取报文体
    // const void* respBody = nullptr;
    // size_t size = 0;
    // resp->get_parsed_body(&respBody, &size);
    char respBody[1024] = {0};
    size_t size = sizeof(respBody);
    resp->get_output_body_merged(respBody, &size);
    cout << endl << (char*) respBody << endl;
}

void redisCallback(WFRedisTask* redisTask) {

    // 1. 检测 redis 状态
    int state = redisTask->get_state();
    int error = redisTask->get_error();
    if (state != WFT_STATE_SUCCESS) {
        cout << WFGlobal::get_error_string(state, error);
        return;
    }

    // 2. 获取 共享数据
    SharedData* context = (SharedData*) series_of(redisTask)->get_context();
    string password = context->password;
    WFHttpTask* httpTask = context->httpTask;


    // 3. 获取 reids 查询结果(响应)
    protocol::RedisResponse* resp = redisTask->get_resp();
    protocol::RedisValue value;
    resp->get_result(value);

    // 4. 生成报文
    if (value.is_string()) {
        // 若信息验证成功, 则生成 成功报文
        if (value.string_value() == password) {
            httpTask->get_resp()->append_output_body("Login Success!");
            return;
        }
    }

    httpTask->get_resp()->append_output_body("Login Failed!");
}

void process(WFHttpTask* httpTask) {

    cout << "\e[93m********************************************************\e[39m" << endl;
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
    }

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


    // 3. 解析请求
    if (method == "GET" && uri =="/login") {

        int fd = open("postform.html", O_RDONLY);
        if (fd == -1) {
            perror("open");
            httpTask->get_resp()->append_output_body("No such file!");
            return;
        }

        char buf[1024] = {0};
        int ret = read(fd, buf, sizeof(buf));
        httpTask->get_resp()->append_output_body(buf, ret);

        close(fd);

    } else if (method == "POST" && uri =="/login") {
        // 3.2.1 获取 用户名 及 密码
        // 密码/用户名 位于 post 报文体中, 格式类似 查询词
        // username=xxxx&password=yyyy
        const void *reqBody = nullptr;
        size_t size = 0;
        req->get_parsed_body(&reqBody, &size);
        string body = (char *)reqBody;
        string usernamePair = body.substr(0, body.find("&"));
        string passwordPair = body.substr(body.find("&") + 1);
        // cout << usernamePair << ": " << passwordPair << endl;
        string username = usernamePair.substr(usernamePair.find("=") + 1);
        string password = passwordPair.substr(passwordPair.find("=") + 1);
        cout << username << ": " << password << endl;

        // 3.2.2 设置 redis 需要用到的 共享数据
        // 即 输入的密码 / httpTask (服务端生成的 httpTask 任务)
        SharedData *context = new SharedData();
        context->httpTask = httpTask;
        context->password = password;
        series_of(httpTask)->set_context(context);

        // 3.2.3 新建 redis 任务, 用于信息验证 和 生成响应报文
        WFRedisTask *redisTask = WFTaskFactory::create_redis_task(
            "redis://localhost", 1, redisCallback);
        // 3.2.4 设置 redis 任务属性
        string command = "get";
        vector<string> params = {username};
        redisTask->get_req()->set_request(command, params);

        // 3.2.5 将 redisTask 加入序列
        series_of(httpTask)->push_back(redisTask);
    }

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




