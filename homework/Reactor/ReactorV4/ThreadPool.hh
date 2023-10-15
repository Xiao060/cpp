#ifndef __THREADPOOL_HPP__
#define __THREADPOOL_HPP__

#include "TaskQueue.hh"
#include "Thread.hh"
#include <cstddef>
#include <functional>
#include <memory>
#include <vector>

using std::vector;
using std::unique_ptr;
using std::function;

class ThreadPool {
    using Task = function<void()>;

public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    void start();
    void stop();

    void addTask(Task&& task);

private:
    // start 中创建线程 时 会将 doTask 绑定到 Thread 的 cb, Thread 创建的子线程 其入口函数 会调用 cb, 即 此处的 doTask
    // getTask 从 队列中取出 任务
    // doTask 将 取出的任务  执行
    Task getTask();
    void doTask();
    
private:
    // 线程数组
    size_t _threadNum;
    vector<unique_ptr<Thread>> _threads;

    // 任务队列
    size_t _queSize;
    TaskQueue _taskQue;

    // 标识 线程池 是否退出
    // 当 线程池 退出时 会唤醒 已阻塞的pop线程, 使其结束阻塞向后运行完毕
    bool isExit;
};

#endif
