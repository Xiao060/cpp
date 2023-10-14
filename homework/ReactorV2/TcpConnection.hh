#ifndef __TCPCONNECTION_HPP__
#define __TCPCONNECTION_HPP__

#include "InetAddress.hh"
#include "Socket.hh"
#include "SocketIO.hh"
#include <functional>
#include <memory>
#include <sys/socket.h>

using std::shared_ptr;
using std::function;


// 每一个 通信的socket 都会建立一个对应的 TcpConnection
class TcpConnection {

    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<void(const TcpConnectionPtr&)>;

public:
    explicit TcpConnection(int fd);
    ~TcpConnection();

    // 用于注册 3 个回调函数, 在 EventLoop 中接收到 新连接时, 创建 tcp 后 调用
    void setNewConnectionCallback(const TcpConnectionCallback&);
    void setMessageCallback(const TcpConnectionCallback&);
    void setCloseCallback(const TcpConnectionCallback&);

    // 调用 3 个 回调函数
    void handleNewConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();

    // 返回 连接信息
    string toString();

    // 调用 SocketIO 完成信息的 接收 与 发送
    string receive();
    void send(const string& msg);

    bool isClosed() const;

private:
    // 用于 初始化 _localAddr / _peerAddr 成员
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();
    
private:
    Socket _sock;    
    SocketIO _socketIO;
    // 用于 打印连接信息
    InetAddress _localAddr;
    InetAddress _peerAddr;

    // 3 个回调函数, 在 EventLoop 中接收到 新连接时, 创建 tcp 后进行 注册
    TcpConnectionCallback _onNewConnectionCb;
    TcpConnectionCallback _onMessageCb;
    TcpConnectionCallback _onCloseCb;
};

#endif
