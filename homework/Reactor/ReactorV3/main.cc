#include "Acceptor.hh"
#include "EventLoop.hh"
#include "InetAddress.hh"
#include "TcpConnection.hh"
#include <iostream>
#include <memory>
#include <unistd.h>

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

    spTcp->send("Hello " + msg);
}

void onClose(const TcpConnectionPtr& spTcp) {
    cout << spTcp->toString() << " has closed!!!" << endl;
}



int main(int argc, char* argv[]) {

    Acceptor acceptor("127.0.0.1", 1234);
    acceptor.ready();

    EventLoop loop(acceptor);
    loop.setNewConnectionCallback(onNewConnection);
    loop.setMessageCallback(onMessage);
    loop.setCloseCallback(onClose);
    loop.loop();

    return 0;
}




