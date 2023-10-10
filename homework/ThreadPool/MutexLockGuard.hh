#ifndef __MUTEXLOCKGUARD_HPP__
#define __MUTEXLOCKGUARD_HPP__


#include "MutexLock.hh"

// 利用 RAII 进行 上锁/解锁

class MutexLockGuard {

public:
    // 构造函数 中  初始化资源 (上锁)
    MutexLockGuard(MutexLock& mutex) 
    : _mutex(mutex) {
        _mutex.lock();
    }
    
    // 在 析构函数 中 释放资源 (解锁)
    ~MutexLockGuard() {
        _mutex.unlock();
    }
    
private:
    MutexLock& _mutex;
    
};

#endif
