#include "TcpServer.hh"
#include <iostream>
#include <memory>
#include <unistd.h>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::shared_ptr;

using TcpConnectionPtr = shared_ptr<TcpConnection>;

void onNewConnection(const TcpConnectionPtr& spTcp) {
    cout << spTcp->toString() << " has connected!!!" << endl;
}

void onMessage(const TcpConnectionPtr& spTcp) {
    string msg = spTcp->receive();
    cout << msg;

    // 在此处进行 任务的处理
    // ...

    spTcp->send("Hello " + msg);
}

void onClose(const TcpConnectionPtr& spTcp) {
    cout << spTcp->toString() << " has closed!!!" << endl;
}



int main(int argc, char* argv[]) {
    TcpServer tcps("127.0.0.1", 1234);

    // QUES: 该函数的 声明中 参数为右值, 为什么 调用时可以传左值
    tcps.setAllCallback(onNewConnection, onMessage, onClose);
    // tcps.setAllCallback(std::move(onNewConnection), std::move(onMessage), std::move(onClose));

    tcps.start();

    return 0;
}




