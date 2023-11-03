// Redis 两个任务串行执行
// 1. 第一个任务的 回调函数中 往当前序列(SeriesWork) 添加新任务
// 第二个任务 若直接使用 redisTask2.start(), 则会另外创建一个序列, 交由另一个子线程执行 (不推荐)
// but 该方法不灵活

#include <csignal>
#include <cstddef>
#include <iostream>


#include <unistd.h>
#include <vector>
#include <workflow/RedisMessage.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


static WFFacilities::WaitGroup waitGruop(2);

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

    if (command == "set") {
        WFRedisTask* redisTask2 = WFTaskFactory::create_redis_task("redis://localhost",
                                                                    1,
                                                                    redisCallback);
        redisTask2->get_req()->set_request("get", {"x"});
        // 将新的任务加入到 当前序列
        series_of(redisTask)->push_back(redisTask2);
    }

    // NOTE: 注意 若将 waitGroup() 的任务书设为 1, 此处两个任务也可以执行完毕
    // 因为 虽然子进程执行 done() 函数将任务数由 1 减为 0, 但是 子进程比父进程运行更快
    // 在父进程的 wait() 侦测到 计数器的变化并且结束主进程之前, 子进程已经完成了 第二个任务
    // but 如果在 done() 后 sleep(1), 则 第二个任务便没有时间执行
    waitGruop.done();
    // sleep(1);
}


int main(int argc, char* argv[]) {

    signal(SIGINT, handler);

    // 1. 拆分为 子任务
    WFRedisTask* redisTask1 = WFTaskFactory::create_redis_task("redis://localhost", 
                                                                1,
                                                                redisCallback);

    // 2. 设置任务属性
    redisTask1->get_req()->set_request("set", {"x", "123"});
    // redisTask1->get_req()->set_request("get", {"x"});
    // redisTask1->get_req()->set_request("hgetall", {"12"});

    // 3. 开始任务
    redisTask1->start();

    waitGruop.wait();

    return 0;
}




