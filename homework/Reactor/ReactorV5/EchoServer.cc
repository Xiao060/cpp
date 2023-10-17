#include "EchoServer.hh"
#include "InetAddress.hh"
#include <functional>
#include <iostream>
#include "TcpConnection.hh"
#include "MyTask.hh"


using TcpConnectionPtr = shared_ptr<TcpConnection>;

using std::cout;
using std::endl;
using std::bind;
using namespace std::placeholders; 


EchoServer::EchoServer(size_t threadNum, size_t queSize, const string& ip, unsigned short port) 
: _pool(threadNum, queSize)
, _server(ip, port) { }

EchoServer::~EchoServer() { }

void EchoServer::start() {
    _pool.start();
    _server.setAllCallback(bind(&EchoServer::onNewConnection, this, _1), 
                           bind(&EchoServer::onMessage, this, _1),
                           bind(&EchoServer::onClose, this, _1));

    _server.start();
}

void EchoServer::stop() {
    _pool.stop();
    _server.stop();
}


void EchoServer::onNewConnection(const TcpConnectionPtr& spTcp) {
    cout << spTcp->toString() << " has connected!!!" << endl;
}

void EchoServer::onMessage(const TcpConnectionPtr& spTcp) {
    string msg = spTcp->receive();
    cout << msg;

    // 在此处进行 任务的处理
    // ...
    MyTask task(msg, spTcp);
    _pool.addTask(bind(&MyTask::process, task));

    // spTcp->send("Hello " + msg);
}

void EchoServer::onClose(const TcpConnectionPtr& spTcp) {
    cout << spTcp->toString() << " has closed!!!" << endl;
}
