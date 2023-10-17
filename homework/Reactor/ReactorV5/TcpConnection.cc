#include "TcpConnection.hh"
#include "EventLoop.hh"
#include "InetAddress.hh"
#include "SocketIO.hh"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <netinet/in.h>
#include <sstream>
#include <string>
#include <sys/socket.h>

using std::ostringstream;
using std::bind;

TcpConnection::TcpConnection(int fd, EventLoop* ploop) 
: _sock(fd) 
, _socketIO(fd) 
, _localAddr(getLocalAddr()) 
, _peerAddr(getPeerAddr()) 
, _loop(ploop) { }

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

// 用于注册 3 个回调函数, 在 EventLoop 中接收到 新连接时, 创建 tcp 后 调用
void TcpConnection::setNewConnectionCallback(const TcpConnectionCallback& cb) {
    _onNewConnectionCb = cb;
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback& cb) {
    _onMessageCb  = cb;
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback& cb) {
    _onCloseCb = cb;
}


// 调用 3 个 回调函数, 在 EventLoop 中 建立新连接(tcp)时 会在 tcp 中注册 3 个回调函数, 
// 当注册完后, EventLoop 会 调用 tcp 的 handleNewConnectionCallback 
// 当已建立的连接 就绪时, 若 未关闭, 则 EventLoop 会调用 tcp 的 handleMessageCallback
// 若连接 关闭, 则 EventLoop 会调用 tcp 的 handleCloseCallback

// 3 个 回调函数 类型为 function<void(const shared_ptr<TcpConnection>&)>, 即参数类型 为 智能指针的 const 引用
// 所以 需要 使 该类 继承 enable_shared_from_this<...>, 然后调用 shared_from_this 函数获取 该对象的智能指针
void TcpConnection::handleNewConnectionCallback() {
    if (_onNewConnectionCb) {
        _onNewConnectionCb(shared_from_this());
    }
}

void TcpConnection::handleMessageCallback() {
    if (_onMessageCb) {
        _onMessageCb(shared_from_this());
    }
}

void TcpConnection::handleCloseCallback() {
    if (_onCloseCb) {
        _onCloseCb(shared_from_this());
    }
}

// ADD:
void TcpConnection::sendInLoop(const string& msg) {
    if (_loop) {
        _loop->storeInLoop(bind(&TcpConnection::send, this, msg));
    }
}
// END: