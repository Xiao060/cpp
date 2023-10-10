#include "TaskQueue.hh"
#include "MutexLock.hh"
#include "Task.hh"
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
, _notFull(_mutex) 
, _flag(true) { }

TaskQueue::~TaskQueue() {

}


void TaskQueue::push(ElemType ptask) {

    // 利用 栈对象 的 生命周期 管理资源
    // 使用 RAII 完成 上锁 / 解锁
    MutexLockGuard autoLock(_mutex);

    while (full()) {
        _notFull.wait();
    }

    _que.push(ptask);
    _notEmpty.notifyAll();
}

ElemType TaskQueue::pop() {

    // 利用 栈对象 的 生命周期 管理资源
    // 使用 RAII 完成 上锁 / 解锁
    MutexLockGuard autoLock(_mutex);

    while (empty() && _flag) {
        _notEmpty.wait();
    }

    ElemType ret = nullptr;
    if (_flag) {
        ret = _que.front();
        _que.pop();
        _notFull.notifyAll();
    }

    return ret;
}

void TaskQueue::wakeup() {
    _flag = false;
    _notEmpty.notifyAll();
}

bool TaskQueue::empty() const {
    return _que.size() == 0;
}

bool TaskQueue::full() const {
    return _que.size() == _queSize;
}
