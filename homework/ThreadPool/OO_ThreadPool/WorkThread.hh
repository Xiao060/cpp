#ifndef __WORKTHREAD_HPP__
#define __WORKTHREAD_HPP__

#include "Thread.hh"
#include "ThreadPool.hh"


class WorkThread 
: public Thread {
public:
    WorkThread(ThreadPool& pool);

    void run() override;

private:
    ThreadPool& _pool;
};

#endif
