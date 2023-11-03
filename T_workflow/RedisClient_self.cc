#include <csignal>
#include <iostream>


#include <workflow/RedisMessage.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>

using std::cin;
using std::cout;
using std::endl;




static WFFacilities::WaitGroup waitGruop(1);

void handler(int signum) {
    waitGruop.done();
}

void redisCallback(WFRedisTask* redisTask) {

    protocol::RedisValue value;
    redisTask->get_resp()->get_result(value);
    cout << value.string_value() << endl;

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
    redisTask->get_req()->set_request("get", {"x"});

    // 3. 开始任务
    redisTask->start();

    waitGruop.wait();

    return 0;
}




