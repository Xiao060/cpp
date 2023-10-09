#include "ThreadPool.hh"
#include "Thread.hh"
#include <memory>

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
}

void ThreadPool::stop() {

}


void ThreadPool::addTask(Task* ptask) {

}

Task* ThreadPool::getTask() {

}

void ThreadPool::doTask() {

}