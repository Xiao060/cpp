#ifndef __MUTEXAUTOLOCK_HPP__
#define __MUTEXAUTOLOCK_HPP__

#include "MutexLock.hh"



class MutexAutoLock {

public:
    MutexAutoLock(MutexLock& mutex) 
    : _mutex(mutex) {
        _mutex.lock();
    }

    ~MutexAutoLock() {
        _mutex.unlock();
    }
    
private:
    MutexLock& _mutex;
};

#endif

