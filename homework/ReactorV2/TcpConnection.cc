#include "TcpConnection.hh"
#include "InetAddress.hh"
#include "SocketIO.hh"
#include <cstddef>
#include <cstdio>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/socket.h>

using std::ostringstream;


TcpConnection::TcpConnection(int fd) 
: _sock(fd) 
, _socketIO(fd) 
, _localAddr(getLocalAddr()) 
, _peerAddr(getPeerAddr()) { }

TcpConnection::~TcpConnection() {

}

string TcpConnection::receive() {
    char buf[1024] = {0};

    int ret = _socketIO.readLine(buf, sizeof(buf));

    if (ret == -1) {
        perror("receive");
    }

    return string(buf);
}

void TcpConnection::send(const string& msg) {
    _socketIO.write(msg.c_str(), msg.size());
}


InetAddress TcpConnection::getLocalAddr() {
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    int ret = getsockname(_sock.getfd(), reinterpret_cast<struct sockaddr*>(&addr), &len);

    if (ret == -1) {
        perror("getsockname");
    }

    return InetAddress(addr);
}

InetAddress TcpConnection::getPeerAddr() {
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    int ret = getpeername(_sock.getfd(), reinterpret_cast<struct sockaddr*>(&addr), &len);

    if (ret == -1) {
        perror("getpeername");
    }

    return InetAddress(addr);
}


string TcpConnection::toString() {

    // char buf[1024];

    // printf("%s:%u -----> %s:%u", _localAddr.getIp().c_str(), _localAddr.getPort(), _peerAddr.getIp().c_str(), _peerAddr.getPort());

    // return string(buf);

    ostringstream oss;

    oss << _localAddr.getIp() << ":" << _localAddr.getPort() << "------->"
        << _peerAddr.getIp() << ":" << _peerAddr.getPort();

    return oss.str();
}
    

bool TcpConnection::isClosed() const {

    char buf[10] = {0};
    int ret = recv(_sock.getfd(), buf, sizeof(buf), MSG_PEEK);

    return ret == 0;
}