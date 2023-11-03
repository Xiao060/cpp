#include <csignal>
#include <cstddef>
#include <iostream>


#include <vector>
#include <workflow/RedisMessage.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;



static WFFacilities::WaitGroup waitGruop(1);

void handler(int signum) {
    waitGruop.done();
}

void redisCallback(WFRedisTask* redisTask) {

    // 检测任务状态
    int state = redisTask->get_state();
    int error = redisTask->get_error();
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
    

    // 1. 获取 请求
    protocol::RedisRequest* req = redisTask->get_req();
    string command;
    vector<string> params;
    req->get_command(command);
    req->get_params(params);
    cout << command << " ";
    for (auto& elem : params) {
        cout << elem << " ";
    }
    cout << endl;


    // 2. 获取 响应
    protocol::RedisResponse* resp = redisTask->get_resp();
    protocol::RedisValue value;
    resp->get_result(value);
    // if (!value.is_ok()) {
    //     cout << "NOT OK" << endl;
    // } else 
    if (value.is_string()) {
        cout << value.string_value() << endl;
    } else if (value.is_int()) {
        cout << value.int_value() << endl;
    } else if (value.is_nil()) {
        cout << "nil" << endl;
    } else if (value.is_array()) {
        for (size_t i = 0; i < value.arr_size(); ++i) {
            cout << i + 1 << ") " << value.arr_at(i).string_value() << endl;
        }
    }

    waitGruop.done();
}


int main(int argc, char* argv[]) {

    signal(SIGINT, handler);

    // 1. 拆分为 子任务
    WFRedisTask* redisTask = WFTaskFactory::create_redis_task("redis://localhost", 
                                                                1,
                                                                redisCallback);

    // 2. 设置任务属性
    // redisTask->get_req()->set_request("set", {"x", "123"});
    // redisTask->get_req()->set_request("get", {"x"});
    redisTask->get_req()->set_request("hgetall", {"12"});

    // 3. 开始任务
    redisTask->start();

    waitGruop.wait();

    return 0;
}




