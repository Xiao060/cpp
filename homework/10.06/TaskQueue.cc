#include "TaskQueue.hh"
#include <cstdio>
#include <queue>
    

TaskQueue::TaskQueue(size_t queSize) 
: _queSize(queSize) 
, _notEmpty(_mutex)
, _notFull(_mutex) { }

TaskQueue::~TaskQueue() {

}


void TaskQueue::push(const int& value) {
    if (full()) {
        perror("TaskQueue is full");
        return ;
    }

    _que.push(value);
}

int TaskQueue::pop() {

    if (empty()) {
        perror("TaskQueue is empty");
        return -1;
    }

    int ret = _que.front();
    _que.pop();

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
