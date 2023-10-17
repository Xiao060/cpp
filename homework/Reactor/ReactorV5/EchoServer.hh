#ifndef __ECHOSERVER_HPP__
#define __ECHOSERVER_HPP__

#include "EventLoop.hh"
#include "ThreadPool.hh"
#include "TcpServer.hh"
#include <cstddef>
#include <functional>
#include <memory>

using std::shared_ptr;

class EchoServer {
    using TcpConnectionPtr = shared_ptr<TcpConnection>;

public:
    EchoServer(size_t threadNum, size_t queSize, const string& ip, unsigned short port);
    ~EchoServer();

    void start();
    void stop();

private:
    void onNewConnection(const TcpConnectionPtr& spTcp);
    void onMessage(const TcpConnectionPtr& spTcp);
    void onClose(const TcpConnectionPtr& spTcp);
    
private:
    ThreadPool _pool;
    TcpServer _server;
};

#endif
