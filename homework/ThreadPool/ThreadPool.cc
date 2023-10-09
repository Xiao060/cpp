#include "ThreadPool.hh"
#include "TaskQueue.hh"
#include "Thread.hh"
#include <memory>
#include "WorkThread.hh"

ThreadPool::ThreadPool(size_t threadNum, size_t queSize) 
: _threadNum(threadNum)
, _queSize(queSize)
, _taskQue(_queSize)
, _isExit(false) {

    _threads.reserve(_threadNum);
}

ThreadPool::~ThreadPool() {

}


void ThreadPool::start() {
    for (int i = 0; i < _threadNum; ++i) {
        unique_ptr<Thread> up(new WorkThread(*this));
        _threads.push_back(std::move(up));
    }

    for (auto& th : _threads) {
        th->start();
    }
}

void ThreadPool::stop() {
    _isExit = true;

    for (auto& th : _threads) {
        th->stop();
    }
}


void ThreadPool::addTask(Task* ptask) {
    if (ptask) {
        _taskQue.push(ptask);
    }
}

Task* ThreadPool::getTask() {
    return _taskQue.pop();
}

void ThreadPool::doTask() {
    while (!_isExit) {
        Task *ptask = getTask();
        if (ptask) {
            ptask->
        }
    }

}