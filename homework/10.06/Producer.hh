#ifndef __PRODUCER_HPP__
#define __PRODUCER_HPP__

#include "TaskQueue.hh"
#include "Thread.hh"


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
