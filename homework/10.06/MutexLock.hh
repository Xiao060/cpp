#ifndef __MUTEXLOCK_HPP__
#define __MUTEXLOCK_HPP__

#include <pthread.h>


class MutexLock {

public:
    MutexLock();
    ~MutexLock();

    void lock();
    void unlock();
    void trylock();
    pthread_mutex_t* getMutexLockPtr();
    
private:
    pthread_mutex_t _mutex;
};

#endif
