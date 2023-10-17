#ifndef __TCPSERVER_HPP__
#define __TCPSERVER_HPP__

#include "Acceptor.hh"
#include "EventLoop.hh"
#include <functional>
#include <memory>

using std::shared_ptr;
using std::function;

class TcpConnection;

class TcpServer {

    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using Callback = function<void(const TcpConnectionPtr&)>;

public:
    TcpServer(const string& ip, unsigned short port);
    ~TcpServer();
    void start();
    void stop();
    void setAllCallback(Callback&& cb1, Callback&& cb2, Callback&& cb3);
    
private:
    Acceptor _acceptor;
    EventLoop _loop; 
};

#endif
