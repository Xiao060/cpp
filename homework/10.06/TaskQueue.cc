#include "TaskQueue.hh"
#include "MutexLockGuard.hh"
#include <cstdio>
#include <iostream>
#include <pthread.h>
#include <queue>


TaskQueue::TaskQueue(size_t queSize) 
: _queSize(queSize) 
, _que()
, _mutex()
, _notEmpty(_mutex)
, _notFull(_mutex) { }

TaskQueue::~TaskQueue() {

}


void TaskQueue::push(const int& value) {

    // 使用 栈对象 的 生存周期 管理资源 (上锁/解锁)
    MutexLockGuard autoLock(_mutex);

    while (full()) {
        _notFull.wait();
    }

    _que.push(value);
    _notEmpty.notifyAll();
}

int TaskQueue::pop() {

    // 使用 栈对象 的 生存周期 管理资源 (上锁/解锁)
    MutexLockGuard autoLock(_mutex);

    while (empty()) {
        _notEmpty.wait();
    }

    int ret = _que.front();
    _que.pop();

    _notFull.notifyAll();

    return ret;
}

bool TaskQueue::empty() const {
    return _que.size() == 0;
}

bool TaskQueue::full() const {
    return _que.size() == _queSize;
}
