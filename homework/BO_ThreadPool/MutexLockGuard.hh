#ifndef __MUTEXLOCKGUARD_HPP__
#define __MUTEXLOCKGUARD_HPP__

#include "MutexLock.hh"


// 使用 栈对象的生命周期 来管理资源, 原理 RAII
class MutexLockGuard {

public: 
    // 创建对象时 获取资源 (上锁)
    MutexLockGuard(MutexLock& mutex) 
    : _mutex(mutex) {
        _mutex.lock();
    }

    // 对象销毁时 释放资源 (解锁)
    ~MutexLockGuard() {
        _mutex.unlock();
    }
    
private:
    MutexLock& _mutex; 
};

#endif
