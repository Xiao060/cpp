#include "TaskQueue.hh"
#include "MutexLock.hh"
#include "MutexLockGuard.hh"
#include <cstddef>
    


TaskQueue::TaskQueue(size_t queSize) 
: _queSize(queSize) 
, _que() 
, _mutex() 
, _notEmpty(_mutex)
, _notFull(_mutex)
, _flag(true) { }

TaskQueue::~TaskQueue() { }


bool TaskQueue::empty() {
    return _que.size() == 0;
}

bool TaskQueue::full() {
    return _que.size() == _queSize;
}


void TaskQueue::push(ElemType&& task) {

    MutexLockGuard autoLock(_mutex);

    while (full()) {
        _notFull.wait();
    }

    _que.push(std::move(task));

    _notEmpty.notify();
}

ElemType TaskQueue::pop() {

    MutexLockGuard autoLock(_mutex);

    while (empty() && _flag) {
        _notEmpty.wait(); 
    }

    ElemType tmp = nullptr;
    if (_flag) {
        tmp = _que.front();
        _que.pop();

        _notFull.notify();
    }

    return tmp;
}

void TaskQueue::wakeup() {
    _flag = false;
    _notEmpty.notifyAll();
}