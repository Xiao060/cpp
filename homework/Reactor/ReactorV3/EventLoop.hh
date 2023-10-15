#ifndef __EVENTLOOP_HPP__
#define __EVENTLOOP_HPP__

#include "Acceptor.hh"
#include "TcpConnection.hh"
#include <cinttypes>
#include <functional>
#include <map>
#include <memory>
#include <vector>
#include <sys/epoll.h>

using std::vector;
using std::map;
using std::shared_ptr;
using std::function;
using std::shared_ptr;


class EventLoop {

    using TcpConnectionPtr = shared_ptr<TcpConnection>;
    using TcpConnectionCallback = function<void(const TcpConnectionPtr&)>;

public:
    EventLoop(Acceptor& acceptor);
    ~EventLoop();

    // 用于初始化 3 个 callback 成员变量
    void setNewConnectionCallback(TcpConnectionCallback&& cb);
    void setMessageCallback(TcpConnectionCallback&& cb);
    void setCloseCallback(TcpConnectionCallback&& cb);
    
    // 
    void loop();
    void unloop();

private:
    // 用于初始化 epfd 成员变量
    int createEpollFd();
    // 用于添加删除监听对象
    void addEpollReadFd(int fd);
    void delEpollReadFd(int fd);

    void waitEpollFd();


    // 创建 tcp 对象, 注册函数, 执行 tcp 的 _onNewConnecctionCb
    void handleNewConnection();
    // 判断 接收信息 / 断开连接, 调用子对象 的 _onMessageCb / _onCloseCb
    void handleMessage(int fd);
    
private:
    int _epfd;
    // 储存 epoll_wait 监听后返回的 epoll_event 
    vector<struct epoll_event> _evtList;
    bool isLooping;
    // 链接器, 用于建立 新的连接 并返回 通信sockfd
    Acceptor& _acceptor;
    // 储存 通信fd 及 对应的TcpConnection
    map<int, shared_ptr<TcpConnection>> _conns;

    // 3 个回调函数, 函数类型为 function<void(const shared_ptr<TcpConnecction>&)> 
    // 会被 Tcp 注册, 然后 Tcp 回调该函数
    TcpConnectionCallback _onNewConnectionCb;
    TcpConnectionCallback _onMessageCb;
    TcpConnectionCallback _onCloseCb;
};

#endif
