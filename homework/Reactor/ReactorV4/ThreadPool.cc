#include "ThreadPool.hh"
#include "TaskQueue.hh"
#include "Thread.hh"
#include <functional>
#include <iostream>
#include <memory>
#include <ostream>
#include <unistd.h>
#include <utility>


using Task = function<void()>;
using std::bind;
using std::cout;
using std::endl;


ThreadPool::ThreadPool(size_t threadNum, size_t queSize) 
: _threadNum(threadNum)
, _threads()
, _queSize(queSize)
, _taskQue(_queSize) 
, isExit(false) {
    // 为 线程数组 重设大小的, 修改 size
    // _threads.resize(_threadNum);
    // 为 线程数组 预留空间, 修改 capacity
    _threads.reserve(_threadNum);
}

ThreadPool::~ThreadPool() {

}


void ThreadPool::start() {
    
    // 创建 线程对象, 并将 cb 设为 doTask
    // 子线程的入口函数 会调用 该 cb 函数
    // doTask 会先 调用 getTask 从 任务队列 取出任务, 然后执行
    for (int i = 0; i < _threadNum; ++i) {
        unique_ptr<Thread> upth(new Thread(bind(&ThreadPool::doTask, this)));
        _threads.push_back(std::move(upth));
    }

    // 创建线程
    for (auto& th : _threads) {
        th->start();
    }
}

void ThreadPool::stop() {

    // NOTE: 保证 任务队列中的 任务全部执行完毕
    // 在线程退出前 需要先将 任务队列中的任务全部执行完毕
    while (!_taskQue.isEmpty()) {
        sleep(1);
    }

    // 执行到此处, 则 任务队列已为空, 但是存在 进程 被 pop 阻塞

    // NOTE: 保证 被 pop 阻塞的线程 能够 摆脱阻塞
    // 线程池退出, 则 唤醒被任务队列 pop 阻塞的线程, 使线程退出阻塞
    isExit = true;
    _taskQue.wakeup();

    // 将 子线程 join, 主线程等待 子线程结束 并 回收子线程资源
    for (auto& th : _threads) {
        th->stop();
    }
}


void ThreadPool::addTask(Task&& task) {
    if (task) {
        _taskQue.push(std::move(task));
    }
}

Task ThreadPool::getTask() {
    return _taskQue.pop();
}


void ThreadPool::doTask() {

    // 线程不退出, 则 取任务 ---> 执行
    while (!isExit) {
        Task task = getTask();

        if (task) {
            task();
        } else {
            cout << "taskcb == nullptr" << endl;
        }
    }
}

