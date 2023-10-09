#ifndef __CONDITION_HPP__
#define __CONDITION_HPP__

#include <pthread.h>

// 1. 直接引入 MutexLock.hh 头文件
// 需要知道类的内部构造时使用, 如 成员子对象
// #include "MutexLock.hh"

// 2. 前向声明
// 不需要知道类的内部构造时使用, 如 指针/引用
// 若使用头文件可能导致 循环包含
class MutexLock;



class Condition {

public:
    Condition(MutexLock& mutex);
    ~Condition();

    void wait();
    void notify();
    void notifyAll();

private:
    MutexLock& _mutex;
    pthread_cond_t _cond;
};

#endif
