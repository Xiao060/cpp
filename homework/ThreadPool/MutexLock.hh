#ifndef __MUTEXLOCK_HPP__
#define __MUTEXLOCK_HPP__

#include <pthread.h>
#include "NonCopyable.hh"

// 互斥锁 / 条件变量 / 线程
// 禁止 拷贝/赋值
// 1. 拷贝/赋值 函数 私有
// 2. 拷贝/赋值 函数 delete
// 3. 继承 NonCopyable 的基类


// 防止 NonCopyable 直接构造对象, 将其设为 抽象类
// 1. 含有 纯虚函数
// 2. 构造/析构 protected


// C++ 默认继承方式 为 私有继承
class MutexLock 
: private NonCopyable {

public:
    MutexLock();
    ~MutexLock();

    void lock();
    void unlock();
    void trylock();

    // 获取 互斥锁
    pthread_mutex_t* getMutexLockPtr();
    
private:
    pthread_mutex_t _mutex;
};

// 防止 死锁, 可以使用 RAII

#endif
