#include "TcpServer.hh"
#include "TcpConnection.hh"
#include <algorithm>


TcpServer::TcpServer(const string& ip, unsigned short port) 
: _acceptor(ip, port)
, _loop(_acceptor) { 

}

TcpServer::~TcpServer() {

}

void TcpServer::start() {
    _acceptor.ready();
    _loop.loop();
}

void TcpServer::stop() {
    _loop.unloop();
}

void TcpServer::setAllCallback(Callback&& cb1, Callback&& cb2, Callback&& cb3) {
    _loop.setNewConnectionCallback(std::move(cb1));
    _loop.setMessageCallback(std::move(cb2));
    _loop.setCloseCallback(std::move(cb3));
}
