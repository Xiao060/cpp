#include <iostream>
#include <ostream>
#include <workflow/HttpMessage.h>
#include <workflow/HttpUtil.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/WFFacilities.h>
#include <csignal>


using std::cout;
using std::endl;


static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo){
    wait_group.done();
}

void callback(WFHttpTask *httpTask) {
    int state = httpTask->get_state();
    int error = httpTask->get_error();

    switch (state){

    case WFT_STATE_SYS_ERROR:
        fprintf(stderr, "system error: %s\n", strerror(error));
        break;

    case WFT_STATE_DNS_ERROR:
        fprintf(stderr, "DNS error: %s\n", gai_strerror(error));
        break;

    case WFT_STATE_SUCCESS:
        break;
    }

    if (state != WFT_STATE_SUCCESS){
        fprintf(stderr, "Failed. Press Ctrl-C to exit.\n");
        return;
    }

    fprintf(stderr, "success\n");
    protocol::HttpRequest *req = httpTask->get_req();
    protocol::HttpResponse *resp = httpTask->get_resp();

    fprintf(stderr, "%s %s %s\r\n", req->get_method(),
                                                    req->get_http_version(),
                                                    req->get_request_uri());

    fprintf(stderr, "%s %s %s\r\n", resp->get_http_version(),
                                                    resp->get_status_code(),
                                                    resp->get_reason_phrase());

    std::string name;
    std::string value;

    // 遍历请求报文的首部字段
    protocol::HttpHeaderCursor req_cursor(req);
    while (req_cursor.next(name, value)){
        fprintf(stderr, "%s: %s\r\n", name.c_str(), value.c_str());
    }
    fprintf(stderr, "\r\n");

    // 遍历响应报文的首部字段
    protocol::HttpHeaderCursor resp_cursor(resp);
    while (resp_cursor.next(name, value)){
        fprintf(stderr, "%s: %s\r\n", name.c_str(), value.c_str());
    }
    fprintf(stderr, "\r\n");


    // 首先需要定义一个指针变量,该指针的基类型是const void
    const void *body;
    size_t body_len;
    // 将指针变量的地址传入get_parsed_body方法中,指针变量将要指向报文体
    resp->get_parsed_body(&body, &body_len);
    fwrite(body, 1, body_len, stdout);
    fflush(stdout);


    wait_group.done();
}

int main(int argc, char *argv[]) {
    std::string url = "http://";
    url.append(argv[1]);

    signal(SIGINT, sig_handler);

    auto httpTask = WFTaskFactory::create_http_task(url, 0, 0, callback);

    protocol::HttpRequest *req = httpTask->get_req();

    req->add_header_pair("Accept", "*/*");
    req->add_header_pair("User-Agent", "TestAgent");
    req->add_header_pair("Connection", "close");

    httpTask->start();


    wait_group.wait();

    return 0;
}