#ifndef __TASKQUEUE_HPP__
#define __TASKQUEUE_HPP__

#include "Condition.hh"
#include "MutexLock.hh"
#include <cstddef>
#include <functional>
#include <queue>


using std::queue;
using std::function;


class TaskQueue {

    using ElemType = function<void()>;
    
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();

    bool isEmpty();
    bool isFull();

    void push(ElemType&& task);
    ElemType pop();

    void wakeup();
    
private:
    MutexLock _mutex;
    Condition _notEmpty;
    Condition _notFull;

    size_t _queSize;
    queue<ElemType> _que;

    bool _flag;
};

#endif
