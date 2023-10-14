#include "ThreadPool.hh"
#include "TaskQueue.hh"
#include "Thread.hh"
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <unistd.h>
#include <utility>

using std::bind;
using std::cout;
using std::endl;


ThreadPool::ThreadPool(size_t threadNum, size_t queSize) 
: _threadNum(threadNum)
, _queSize(queSize)
, _threads()
, _taskQue(queSize)
, _isExit(false) { 

    _threads.reserve(_threadNum);
}

ThreadPool::~ThreadPool() { }


void ThreadPool::start() {

    for (size_t i = 0; i < _threadNum; ++i) {
        unique_ptr<Thread> up(new Thread(bind(&ThreadPool::doTask, this)));
        _threads.push_back(std::move(up));
    }

    for (auto& th : _threads) {
        th->start();
    }
}

void ThreadPool::stop() {
    // 先要检查 任务队列是否为空, 不为空 则等待, 为空则退出

    while (!_taskQue.empty()) {
        sleep(1);
    }

    _isExit = true;
    _taskQue.wakeup();

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

    // 进程状态 不为退出, 便要 一直执行任务
    while (!_isExit) {
        Task taskcb = getTask();

        if (taskcb) {
            taskcb();
        } else {
            cout << "taskcb == nullptr" << endl;
        }
    }
}
