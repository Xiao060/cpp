#include "Thread.hh"
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <pthread.h>

using std::cout;
using std::endl;



Thread::Thread(ThreadCallBack cb) 
: _isRunning(false)
, _cb(cb) { }

Thread::~Thread() {

}


void Thread::start() {
    // 此处 第3个 参数为 void*(void*) 的函数指针
    // 故 需要把 ThreadFunc 设为 静态成员函数, 否则 会 有一个 this 指针
    int ret = pthread_create(&_thid, nullptr, ThreadFunc, this);

    if (ret) {
        perror("pthread_create");
        return ;
    }

    _isRunning = true;
}

void Thread::stop() {

    if (_isRunning) {
        int ret = pthread_join(_thid, nullptr);

        if (ret) {
            perror("pthread_join");
            return;
        }

        _isRunning = false;
    }
}

void* Thread::ThreadFunc(void* args) {
    Thread* pth = static_cast<Thread*>(args);

    if (pth) {
        pth->_cb();
    } else {
        cout << "pth == nullptr" << endl;
    }

    // pth 指针为空, 无任务执行, 子线程退出
    pthread_exit(nullptr);
}