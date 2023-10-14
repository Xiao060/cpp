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
using std::enable_shared_from_this;

// 每一个 通信的socket 都会建立一个对应的 TcpConnection
// 因为 该类的 3 个 回调函数 类型为 function<void(const shared_ptr<TcpConnection>&)>
// 即 参数为 该 tcp 的 智能指针, 则 需要让 该类 继承 enable_shared_from_this<...> 类
// 然后 使用 shared_from_this 获取当前对象的智能指针
class TcpConnection 
: public enable_shared_from_this<TcpConnection> {

    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<void(const TcpConnectionPtr&)>;

public:
    explicit TcpConnection(int fd);
    ~TcpConnection();

    // 用于注册 3 个回调函数, 在 EventLoop 中接收到 新连接时, 创建 tcp 后 调用
    void setNewConnectionCallback(const TcpConnectionCallback& cb);
    void setMessageCallback(const TcpConnectionCallback& cb);
    void setCloseCallback(const TcpConnectionCallback& cb);

    // 调用 3 个 回调函数, 在 EventLoop 中 建立新连接(tcp)时 会在 tcp 中注册 3 个回调函数, 
    // 当注册完后, EventLoop 会 调用 tcp 的 handleNewConnectionCallback 
    // 当已建立的连接 就绪时, 若 未关闭, 则 EventLoop 会调用 tcp 的 handleMessageCallback
    // 若连接 关闭, 则 EventLoop 会调用 tcp 的 handleCloseCallback
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
    // 返回 InetAddress 对象, 
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
    // 3 个回调函数 的 类型为 function<void(const shared_ptr<TcpConnection>&)>
    // 即 函数需要的参数 是 智能指针 的 const 引用, 即 我们需要获取 该 tcp 的 智能指针
    // QUES: 回调函数的 参数 为什么使用 智能指针, tcp 已存储于 EventLoop 的 map 中
    // NOTE: 使用 智能指针作为参数, 则 我们需要获取当前 tcp 的 智能指针
    // 需要 使 该类继承 enable_shared_from_this<...>, 使用 shared_from_this() 获取该 对象的 智能指针
    TcpConnectionCallback _onNewConnectionCb;
    TcpConnectionCallback _onMessageCb;
    TcpConnectionCallback _onCloseCb;
};

#endif
