#ifndef __TASKQUEUE_HPP__
#define __TASKQUEUE_HPP__

#include <cstddef>
#include <functional>
#include <queue>
#include "Condition.hh"
#include "MutexLock.hh"

using std::queue;
using std::function;

using ElemType = function<void()>;


class TaskQueue {

public:
    TaskQueue(size_t queSize);
    ~TaskQueue();

    bool empty();
    bool full();

    void push(ElemType&& task);
    ElemType pop();

    // 用于唤醒 在 _notEmpty 队列中等待的 线程
    void wakeup();
    
private:
    size_t _queSize;
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notEmpty;
    Condition _notFull;

    // 用于 退出 条件变量队列
    bool _flag;
};

#endif
