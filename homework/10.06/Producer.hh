#ifndef __PRODUCER_HPP__
#define __PRODUCER_HPP__

#include "Thread.hh"

// #include "TaskQueue.hh"
// 此处使用的是 引用, 使用 前向声明
class TaskQueue;

class Producer 
: public Thread {

public:
    Producer(TaskQueue& taskQue);
    ~Producer();

    void run() override;
    
private:
    TaskQueue& _taskQue;    
};

#endif
