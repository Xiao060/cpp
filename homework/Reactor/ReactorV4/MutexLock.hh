#ifndef __MUTEXLOCK_HPP__
#define __MUTEXLOCK_HPP__

#include "NonCopyable.hh"
#include <pthread.h>


class MutexLock 
: NonCopyable {
public:
    MutexLock();
    ~MutexLock();

    void lock();
    void trylock();
    void unlock();

    // 同步 的 wait() 需要用到 互斥锁
    pthread_mutex_t* getMutexLockPtr();
    
private:
    pthread_mutex_t _mutex;
};

#endif
