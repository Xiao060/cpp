#include "TaskQueue.hh"
#include "MutexAutoLock.hh"
#include "MutexLock.hh"


using ElemType = function<void()>;


TaskQueue::TaskQueue(size_t queSize) 
: _mutex()
, _notEmpty(_mutex)
, _notFull(_mutex) 
, _queSize(queSize)
, _que() 
, _flag(true) { }

TaskQueue::~TaskQueue() {
    _flag = false; 
}


bool TaskQueue::isEmpty() {
    return _que.size() == 0;
}

bool TaskQueue::isFull() {
    return _que.size() == _queSize;
}


void TaskQueue::push(ElemType&& task) {
    MutexAutoLock mutex(_mutex);

    while (isFull()) {
        _notFull.wait();
    }

    _que.push(task);
}

ElemType TaskQueue::pop() {
    MutexAutoLock mutex(_mutex);

    while (isEmpty()) {
        _notEmpty.wait();
    }

    ElemType elem = _que.front();
    _que.pop();

    return elem;
}

void TaskQueue::wakeup() {

}