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

    // 当 线程池 退出时 不会再有新的任务 push, 但是 之前会有线程被阻塞在 pop
    // wakeup 函数的作用就是 唤醒 notEmpty 中的所有线程 并 将它们继续向下执行
    void wakeup();
    
private:
    MutexLock _mutex;
    Condition _notEmpty;
    Condition _notFull;

    size_t _queSize;
    queue<ElemType> _que;
    
    // 标识 线性池(任务队列) 是否 退出
    // 若 线程池 退出, 则 已阻塞的pop线程 需要被唤醒继续向后执行
    // 则 任务出队时 只有 任务队列未退出 且 队列为空时 才阻塞
    bool _isAlive;
};

#endif
