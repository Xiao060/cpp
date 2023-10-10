#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include "NonCopyable.hh"
#include <iostream>
#include <pthread.h>

using std::cout;
using std::endl;

/*****************************************************************************/
/*                               头文件                                      */
/****************************************************************************/

// 默认继承方式 为 私有继承
class Thread 
: NonCopyable {
public:
    Thread();
    virtual ~Thread();

    void start();
    void stop();

private:
    // pthread_create 第三个参数 类型为 参数为 void*, 返回值为 void* 的函数指针
    // 若 threadFunc 作为 非静态 成员函数, 则 至少有一个参数 this 指针
    // 故 应该把 threadFunc 设为 静成员函数
    static void* threadFunc(void* args);
    virtual void run() = 0;

    pthread_t _thid;
    bool _isRunning;
};


#endif