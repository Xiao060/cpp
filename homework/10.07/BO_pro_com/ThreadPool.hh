#ifndef __THREADPOOL_HPP__
#define __THREADPOOL_HPP__

#include "TaskQueue.hh"
#include <cstddef>
#include <functional>
#include <memory>
#include <vector>

using std::vector;
using std::unique_ptr;
using std::function;

using Task = function<void()>;

class Thread;

class ThreadPool {

public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    void start();
    void stop();
    
    void addTask(Task&& task);

private: 
    Task getTask();
    void doTask();
    
private:
    size_t _threadNum;
    size_t _queSize;
    vector<unique_ptr<Thread>> _threads;
    TaskQueue _taskQue;
    bool _isExit;
};

#endif
