#include "TaskQueue.hh"
#include "MutexAutoLock.hh"
#include "MutexLock.hh"
#include <utility>


using ElemType = function<void()>;


TaskQueue::TaskQueue(size_t queSize) 
: _mutex()
, _notEmpty(_mutex)
, _notFull(_mutex) 
, _queSize(queSize)
, _que() 
, _isAlive(true) { }

TaskQueue::~TaskQueue() { }


bool TaskQueue::isEmpty() {
    return _que.size() == 0;
}

bool TaskQueue::isFull() {
    return _que.size() == _queSize;
}


void TaskQueue::push(ElemType&& task) {
    MutexAutoLock autoLock(_mutex);

    while (isFull()) {
        _notFull.wait();
    }

    _que.push(std::move(task));

    _notEmpty.notify();
}

ElemType TaskQueue::pop() {
    MutexAutoLock autoLock(_mutex);

    // 出队时 只有 任务队列未退出 且 任务队列为空 才阻塞
    while (_isAlive && isEmpty()) {
        _notEmpty.wait();
    }

    // 若 线程池已退出, 则 直接返回 nullptr
    // 若 未退出, 则正常pop, 并唤醒 _notFull 队列
    ElemType task;
    if (_isAlive) {
        task = _que.front();
        _que.pop();
        _notFull.notify();
    } else {
        task = nullptr;
    }

    return task;
}

void TaskQueue::wakeup() {
    _isAlive = false;
    _notEmpty.notifyAll();
}