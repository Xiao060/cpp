#ifndef __CONSUMER_HPP__
#define __CONSUMER_HPP__

#include "TaskQueue.hh"
#include "Thread.hh"


class Consumer 
: public Thread {

public:
    Consumer(TaskQueue& taskQue);
    ~Consumer();

    void run() override;
    
private:
    TaskQueue& _taskQue;
};

#endif
