#include <iostream>
#include <ostream>
#include <string>
#include <workflow/RedisMessage.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/WFFacilities.h>
#include <csignal>

using std::string;
using std::cout;
using std::endl;


void redis_callback(WFRedisTask *task){

    protocol::RedisRequest *req = task->get_req();
    protocol::RedisResponse *resp = task->get_resp();
    protocol::RedisValue val;

    int state = task->get_state();
    int error = task->get_error();

    switch (state){

    case WFT_STATE_SYS_ERROR:
        fprintf(stderr, "system error: %s\n", strerror(error));
        break;
    case WFT_STATE_DNS_ERROR:
        fprintf(stderr, "DNS error: %s\n", gai_strerror(error));
        break;
    case WFT_STATE_SUCCESS:
        resp->get_result(val);

        if (val.is_error()) {
            fprintf(stderr, "Error reply. Need a password?\n");
            state = WFT_STATE_TASK_ERROR;
        }
        break;
    }

    if (state != WFT_STATE_SUCCESS) {
        fprintf(stderr, "Failed. Press Ctrl-C to exit.\n");
        return;
    }

    if(val.is_array()){
        for(int i = 0; i < val.arr_size(); ++i){
            auto ele = val.arr_at(i);
            fprintf(stderr,"REDIS HGETALL %d = %s\n", i,
            ele.string_value().c_str());
        }
    }

}

static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo){
    wait_group.done();
}

int main(int argc, char *argv[]){

    signal(SIGINT, sig_handler);

    string url = "redis://127.0.0.1:6379";

    WFRedisTask *task = WFTaskFactory::create_redis_task(url, 2, redis_callback);
    protocol::RedisRequest *req = task->get_req();
    // req->set_request("HSET", { "HMAP1","key1", "value1" });
    req->set_request("HGETALL", { "HMAP1" });
    task->start();

    wait_group.wait();
    return 0;
}