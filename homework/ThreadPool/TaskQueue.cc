#include "TaskQueue.hh"
#include "Task.hh"
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


void TaskQueue::push(ElemType value) {

    _mutex.lock();

    while (full()) {
        _notFull.wait();
    }

    _que.push(value);

    _mutex.unlock();
    _notEmpty.notifyAll();
}

ElemType TaskQueue::pop() {
    _mutex.lock();

    while (empty() && _flag) {
        _notEmpty.wait();
    }

    ElemType ret = _que.front();
    _que.pop();

    _mutex.unlock();
    _notFull.notifyAll();

    return ret;
}

void TaskQueue::wakeup() {
    _flag = false;
    _notEmpty.notifyAll();
}

bool TaskQueue::empty() {
    return _que.size() == 0;
}

bool TaskQueue::full() {
    return _que.size() == _queSize;
}
