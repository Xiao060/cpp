#ifndef __MUTEXLOCK_HPP__
#define __MUTEXLOCK_HPP__

#include "NonCopyable.hh"
#include <pthread.h>

// 互斥锁 / 条件变量 / 线程
// 禁止 拷贝/赋值
// 1. 拷贝/赋值 函数 私有
// 2. 拷贝/赋值 函数 delete
// 3. 继承 NonCopyable 的基类


// 防止 NonCopyable 直接构造对象, 将其设为 抽象类
// 1. 含有 纯虚函数
// 2. 构造/析构 protected


// 默认继承 为 私有继承
class MutexLock 
: NonCopyable {
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

// 防止 死锁, 可以使用 RAII

#endif
