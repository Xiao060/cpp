#include "Thread.hh"
#include <cstddef>
#include <cstdio>
#include <functional>
#include <iostream>
#include <ostream>
#include <pthread.h>
#include <utility>

// using std::bind;
// using namespace std::placeholders;
using std::cout;
using std::endl;


Thread::Thread(ThreadCallback&& cb) 
: _thid(0)
, _cb(std::move(cb))
, isRunning(false) { }

Thread::~Thread() { }

void Thread::start() {
    //  pthread_create
    // 参数 3: 为 子线程的 入口函数, 类型为 void*(void*), 如果该函数为普通成员函数, 则 其类型为 void*(Thread*, void*)
    //         解决方案: 将 该函数设为 静态成员函数; 
    //         QUES: 将 该函数 用 bind 绑定 可以吗 ???
    int ret = pthread_create(&_thid, nullptr, threadFunc, this);
    // function<void*(void*)> x = bind(&Thread::threadFunc, this, _1);
    // int ret = pthread_create(&_thid, nullptr, x.target<void*(void*)>() , this);

    if (ret) {
        perror("pthread_create");
        return;
    }

    isRunning = true;
}

void Thread::stop() {

    if (isRunning) {
        int ret = pthread_join(_thid, nullptr);

        if (ret) {
            perror("pthread_join");
            return;
        }
        isRunning = false;
    }
}

void* Thread::threadFunc(void* args) {
    Thread* pth = static_cast<Thread*>(args);

    if (pth) {
        pth->_cb();
    } else {
        cout << "pth == nullptr" << endl;
    }

    pthread_exit(nullptr);
}
