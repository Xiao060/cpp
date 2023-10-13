#ifndef __TCPCONNECTION_HPP__
#define __TCPCONNECTION_HPP__

#include "InetAddress.hh"
#include "Socket.hh"
#include "SocketIO.hh"
#include <sys/socket.h>


// 每一个 通信的socket 都会建立一个对应的 TcpConnection
class TcpConnection {

public:
    explicit TcpConnection(int fd);
    ~TcpConnection();


    // 用于 初始化 _localAddr / _peerAddr 成员
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();
    // 返回 连接信息
    string toString();


    // 调用 SocketIO 完成信息的 接收 与 发送
    string receive();
    void send(const string& msg);

    bool isClosed();


    
    
    
    
private:
    Socket _sock;    
    SocketIO _socketIO;
    // 用于 打印连接信息
    InetAddress _localAddr;
    InetAddress _peerAddr;
};

#endif
