#include "TaskQueue.hh"
#include <cstdio>
#include <iostream>
#include <pthread.h>
#include <queue>


TaskQueue::TaskQueue(size_t queSize) 
: _queSize(queSize) 
, _notEmpty(_mutex)
, _notFull(_mutex) { }

TaskQueue::~TaskQueue() {

}


void TaskQueue::push(const int& value) {

    _mutex.lock();

    while (full()) {
        _notFull.wait();
    }

    _que.push(value);

    _mutex.unlock();
    _notEmpty.notifyAll();
}

int TaskQueue::pop() {
    _mutex.lock();

    while (empty()) {
        _notEmpty.wait();
    }

    int ret = _que.front();
    _que.pop();

    _mutex.unlock();
    _notFull.notifyAll();

    return ret;
}

bool TaskQueue::empty() {
    if (_que.size() == 0) {
        return true;
    }

    return false;
}

bool TaskQueue::full() {
    if (_que.size() == _queSize) {
        return true;
    }

    return false;
}
