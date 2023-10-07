#ifndef __TASKQUEUE_HPP__
#define __TASKQUEUE_HPP__

#include "MutexLock.hh"
#include <queue>
#include "Condition.hh"

using std::queue;

class TaskQueue {

public:
    TaskQueue(size_t queSize);
    ~TaskQueue();

    void push(const int& value);
    int pop();
    
private:
    bool empty();
    bool full();

    size_t _queSize;   
    queue<int> _que;
    MutexLock _mutex;
    Condition _notEmpty;
    Condition _notFull;
};

#endif
