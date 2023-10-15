#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <functional>

using std::function;

class Thread {
    using ThreadCallback = function<void()>;

public:
    Thread(ThreadCallback&& cb);
    ~Thread();

    void start();
    void stop();

private:
    static void* threadFunc(void* args);
    
private:
    pthread_t _thid;
    ThreadCallback _cb;
    // 标识 进程是否结束, stop() 停止线程时检查, 可以防止 重复 stop
    bool isRunning;
};

#endif
