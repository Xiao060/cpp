#include "MyTask.hh"
#include "TcpConnection.hh"
#include "TcpServer.hh"
#include "ThreadPool.hh"
#include <functional>
#include <iostream>
#include <memory>
#include <unistd.h>
#include <utility>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::bind;

using TcpConnectionPtr = shared_ptr<TcpConnection>;

// 全局变量 线程池
ThreadPool* gPool = nullptr;


void onNewConnection(const TcpConnectionPtr& spTcp) {
    cout << spTcp->toString() << " has connected!!!" << endl;
}

void onMessage(const TcpConnectionPtr& spTcp) {
    string msg = spTcp->receive();
    cout << msg;

    // 在此处进行 任务的处理
    // ...
    MyTask task(msg, spTcp);
    gPool->addTask(bind(&MyTask::process, task));

    // spTcp->send("Hello " + msg);
}

void onClose(const TcpConnectionPtr& spTcp) {
    cout << spTcp->toString() << " has closed!!!" << endl;
}



int main(int argc, char* argv[]) {

    ThreadPool pool(4, 10);
    pool.start(); 
    gPool =  &pool;


    TcpServer tcps("127.0.0.1", 1234);

    // QUES: 该函数的 声明中 参数为右值, 为什么 调用时可以传左值
    // NOTE: C 语言 函数名即函数指针比较特殊, 即可看作左值也可看作右值
    tcps.setAllCallback(onNewConnection, onMessage, onClose);
    // tcps.setAllCallback(std::move(onNewConnection), std::move(onMessage), std::move(onClose));

    tcps.start();

    return 0;
}




