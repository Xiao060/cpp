// 借助 ParallelWork, 完成并行任务
// ParallelWork 是一个任务, 需要放入 序列中(调度)执行 
// ParallelWork 的基本单位 是 序列


#include <csignal>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>

#include <sys/types.h>
#include <vector>
#include <workflow/HttpMessage.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>
// 用于获取 http 的首部字段, 即 protocol::HttpHeaderCursor
#include <workflow/HttpUtil.h>


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


WFFacilities::WaitGroup waitGroup(4);

void handler(int signum) {
    cout << "signum: " << signum << endl;
    waitGroup.done();
}


void httpCallback(WFHttpTask* httpTask) {
    int state = httpTask->get_state();
    int error = httpTask->get_error();

    switch (state) {
    case WFT_STATE_SUCCESS: 
        break;
    case WFT_STATE_SYS_ERROR:
        cout << "Sys Error: " << strerror(error) << endl;
        // break;
        return;
    case WFT_STATE_DNS_ERROR:
        cout << "DNS Error: " << gai_strerror(error) << endl;
        return; 
    default:
        cout << "Error: " << strerror(error) << endl;
        return; 
    }

    // 1. 获取 请求
    protocol::HttpRequest* req = httpTask->get_req();
    // 1.1 获取 起始行, 请求方法/路径/协议版本
    string reqMethod = req->get_method();
    string reqUri = req->get_request_uri();
    string reqVersion = req->get_http_version();
    cout << reqMethod << " " << reqUri << " " << reqVersion << endl;
    // 2.1 获取 首部字段
    protocol::HttpHeaderCursor reqCursor(req);
    string key, value;
    while (reqCursor.next(key, value)) {
        cout << "\e[93m" << key << "\e[39m: " << value << endl;
    }

    // 2. 获取 响应
    protocol::HttpResponse* resp = httpTask->get_resp();
    // 2.1 获取 起始行, 协议版本/状态码/原因短语
    string respVersion = resp->get_http_version();
    string respCode = resp->get_status_code();
    string respPhrase = resp->get_reason_phrase();
    cout << respVersion << " " << respCode << " " << respPhrase << endl;
    // 2.1 获取 首部字段
    protocol::HttpHeaderCursor respCursor(resp);
    while (respCursor.next(key, value)) {
        cout << "\e[93m" << key << "\e[39m: " << value << endl;
    }
    // 2.2 获取 报文体
    const void* body = nullptr;
    size_t size = 0;
    resp->get_parsed_body(&body, &size);
    cout << "\e[93mbody:\e[39m " << (char*)body << endl;
    
    cout << "\e[93m**********************************************************\e[39m" << endl;

    waitGroup.done();
}

void parallelCallback(const ParallelWork* parallelWork) {
    cout << "parallelWork Callbacck" << endl;
    waitGroup.done();
}


int main(int argc, char* argv[]) {

    signal(SIGINT, handler);

    vector<string> host = {"http://www.baidu.com", 
                            "http://www.alibaba.com",
                            "http://codexiao.top" };


    // 创建 ParallelWork 任务
    ParallelWork* parallelWork = Workflow::create_parallel_work(parallelCallback);

    for (int i = 0; i < host.size(); ++i) {

        // 创建子任务  
        WFHttpTask* httpTask = WFTaskFactory::create_http_task(host[i],
                                                                1, 
                                                                1, 
                                                                httpCallback);
        // 设置子任务属性 
        // ...

        // 创建序列, 并将子任务加入序列
        SeriesWork* series = Workflow::create_series_work(httpTask, nullptr);

        // 将序列加入 ParallelWork
        parallelWork->add_series(series);
    }

    // 调度执行 ParallelWork 任务
    // 1. 直接调用 start(), 不灵活, 不能设置 序列 的回调函数
    // parallelWork->start();
    // 2. 先创建 最外层序列, 在手动调用
    SeriesWork* seriesOunter = Workflow::create_series_work(parallelWork, nullptr);
    seriesOunter->start();

    waitGroup.wait();

    return 0;
}




