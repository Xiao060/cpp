#ifndef __CONDITION_HPP__
#define __CONDITION_HPP__

#include "NonCopyable.hh"
#include <pthread.h>


class MutexLock;

class Condition 
: NonCopyable {

public:
    Condition(MutexLock& mutex);
    ~Condition();

    void wait();
    void notify();
    void notifyAll();
    
private:
    pthread_cond_t _cond;
    MutexLock& _mutex;
};

#endif
