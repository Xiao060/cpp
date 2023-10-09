#ifndef __TASKQUEUE_HPP__
#define __TASKQUEUE_HPP__

#include <queue>
// 此处 含有 3 个成员子对象, 直接 包含头文件
#include "MutexLock.hh"
#include "Condition.hh"
using std::queue;

class Task;
using ElemType = Task*;

class TaskQueue {
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();

    void push(ElemType value);
    ElemType pop();
    
private:
    bool empty();
    bool full();

    size_t _queSize;   
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notEmpty;
    Condition _notFull;
};

#endif
