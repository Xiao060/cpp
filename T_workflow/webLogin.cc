// Http 服务器


#include <csignal>
#include <iostream>


// 用于阻塞 主线程
#include <workflow/WFFacilities.h>
// 用于创建 http 服务器
#include <workflow/WFHttpServer.h>
// 用于创建 任务
#include <workflow/WFTaskFactory.h>


using std::cin;
using std::cout;
using std::endl;


static WFFacilities::WaitGroup waitGroup(1);

void handler(int signo) {

    waitGroup.done();
}


void process(WFHttpTask* httpTask) {
    cout << "httpServerCallback" << endl;
}


int main(int argc, char* argv[]) {

    signal(SIGINT, handler);

    // 1. 创建 httpServer, 设置 其 process 函数
    // 启动 http 服务器时会 自动创建 http服务端任务, 并放入序列调度执行
    // 1.1 服务器 先接收 客户端 请求报文
    // 1.2 然后 由 process函数 解析请求, 生成响应; 
    // 故 process 参数为 WFHttpTask, 即 httpServer 自动创建的 http服务端任务
    // 1.3 最后再由 服务器 发送请求
    WFHttpServer httpServer(process);



    if (httpServer.start(8888) == 0) {
        cout << "启动成功" << endl;
        waitGroup.wait();
        httpServer.stop();
    }

    return 0;
}




