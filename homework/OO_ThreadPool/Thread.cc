#include "Thread.hh"

Thread::Thread() 
: _thid(0)
, _isRunning(false) { }

Thread::~Thread() {}

void Thread::start() {
    // pthread_create 第三个参数 类型为 参数为 void*, 返回值为 void* 的函数指针
    // 若 threadFunc 作为 非静态 成员函数, 则 至少有一个参数 this 指针
    // 故 应该把 threadFunc 设为 静成员函数
    int ret = pthread_create(&_thid, nullptr, threadFunc, this);

    if (ret) {
        perror("pthread_creat");
        return;
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
    

void* Thread::threadFunc(void* args) {
    Thread* pth = static_cast<Thread*>(args);

    if (pth) {
        pth->run();
    } else {
        cout << "pth == nullptr" << endl;
    }

    // 若 this 指针为空, 则 子线程无任务执行, 直接结束
    pthread_exit(nullptr);
}