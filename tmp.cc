#include <functional>
#include <iostream>
#include <memory>
#include <pthread.h>
#include <unistd.h>

using std::cout;
using std::endl;
using std::function;
using std::bind;
using std::unique_ptr;

class Thread {
public:
    using ThreadCallback = function<void()>;

    Thread(ThreadCallback&& cb);
    ~Thread();

    void start();
    void stop();

private:
    static void* threadFunc(void* args);

    pthread_t _thid;
    bool _isRunning;
    ThreadCallback _cb;
};
    

Thread::Thread(ThreadCallback&& cb) 
: _thid(0)
, _isRunning(false)
, _cb(std::move(cb)) { }

Thread::~Thread() { }

void Thread::start() {

    int ret = pthread_create(&_thid, nullptr, threadFunc, this);

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
            return ;
        }
        _isRunning = false;
    }
}

void* Thread::threadFunc(void* args) {
    Thread* pth = static_cast<Thread*>(args);
    
    if (pth) {
        pth->_cb();
    } else {
        cout << "pth == nullptr" << endl;
    }

    // return nullptr;
    pthread_exit(nullptr);
}


// void test() {

//     while (1) {
//         cout << "Hello" << endl;
//         sleep(1);
//     }
// }


class MyTask {
public:
    void task() {
        while (1) {
            cout << "Hello" << endl;
            sleep(1);
        }
    }
};


int main() {

    // unique_ptr<Thread> pth(new Thread(bind(test)));

    MyTask my;
    unique_ptr<Thread> pth(new Thread(bind(&MyTask::task, &my)));

    pth->start();
    pth->stop();

    return 1;
}