#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <functional>
#include <pthread.h>

using std::function;
using ThreadCallBack = function<void()>;



class Thread {

public:
    Thread(ThreadCallBack cb);
    ~Thread();

    void start();
    void stop();
    static void* ThreadFunc(void* args);
    
private:
    pthread_t _thid; 
    bool _isRunning;
    ThreadCallBack _cb;
};

#endif
