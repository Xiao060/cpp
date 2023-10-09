#include "TaskQueue.hh"
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

    while (empty()) {
        _notEmpty.wait();
    }

    ElemType ret = _que.front();
    _que.pop();

    _mutex.unlock();
    _notFull.notifyAll();

    return ret;
}

bool TaskQueue::empty() {
    return _que.size() == 0;
}

bool TaskQueue::full() {
    return _que.size() == _queSize;
}
