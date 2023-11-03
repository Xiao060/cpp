// Redis 两个任务串行 共享数据
// 2. 序列中存在一个 void* context 指向共享数据
// 此时共享数据为 堆上的数据, 需要释放
// 1. 手动释放
// 2. 注册 序列(SeriesWork) 的 (共享)资源清理函数

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

    // 打印共享数据
    SeriesWork* series = series_of(redisTask);
    ++*((int*) series->get_context());
    cout << "num: " << *((int*) series->get_context()) << endl;
    cout << "pnum: " << series->get_context() << endl;

    // NOTE: 注意 若将 waitGroup() 的任务书设为 1, 此处两个任务也可以执行完毕
    // 因为 虽然子进程执行 done() 函数将任务数由 1 减为 0, 但是 子进程比父进程运行更快
    // 在父进程的 wait() 侦测到 计数器的变化并且结束主进程之前, 子进程已经完成了 第二个任务
    // but 如果在 done() 后 sleep(1), 则 第二个任务便没有时间执行
    waitGruop.done();
    // sleep(1);
}


// 序列的 (共享)资源清理函数
void seriesCallback(const SeriesWork* series) {
    int* pnum = (int*) series->get_context();
    if (pnum) {
        delete pnum;
    }
}


int main(int argc, char* argv[]) {

    signal(SIGINT, handler);

    // 用于共享的数据, 此时共享数据为 堆上的数据, 需要释放
    int* pnum = new int(100);
    cout << "num: " << *pnum << endl;
    cout << "pnum: " << pnum << endl;


    // 1.1 第一个任务
    WFRedisTask* redisTask1 = WFTaskFactory::create_redis_task("redis://localhost", 
                                                                1,
                                                                redisCallback);
    // 1.2 设置任务属性
    redisTask1->get_req()->set_request("hset", {"x", "y", "123"});


    // 2.1 第二个任务
    WFRedisTask* redisTask2 = WFTaskFactory::create_redis_task("redis://localhost", 
                                                                1,
                                                                redisCallback);
    // 2.2 设置任务属性
    redisTask2->get_req()->set_request("hgetall", {"x"});

    // 3. 手动建立序列, 第二个参数 释放序列共享数据 context 的 回调函数
    // 序列中的 最后一个任务执行完毕后会自动销毁 序列
    // 猜测 通过 series_of() 获取序列, 然后使用 delete 释放序列
    SeriesWork* series = Workflow::create_series_work(redisTask1, nullptr);
    series->push_back(redisTask2);

    // 设置 序列的共享数据
    series->set_context(pnum);
    // 设置 序列的 (共享)资源清理函数
    series->set_callback(seriesCallback);

    // 4. 开始任务
    series->start();

    waitGruop.wait();
    
    // 手动释放
    // delete pnum;

    return 0;
}




