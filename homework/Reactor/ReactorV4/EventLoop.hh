#ifndef __EVENTLOOP_HPP__
#define __EVENTLOOP_HPP__

#include "Acceptor.hh"
#include "MutexLock.hh"
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
    // ADD:
    using Functor = function<void()>;
    // END:

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

    // ADD:
    // tcp 调用 handleMessage 处理 任务
    // 即 调用 tcp 中的回调函数 先对任务进行预处理
    // 然后 回调函数会 将 [业务 + tcp] 添加到 线程池的任务队列中
    // 线程池 将 业务 处理完毕后 会将 [业务 + tcp] 通过 tcp 的 sendInLoop 添加到 eventloop 的 待发送数组中
    // sendInLoop 实际是调用 eventloop 的 storeInLoop 函数
    // storeInLoop 函数 先将 [业务 + tcp] 储存在待发送数组 后, 然后会调用 wakeup 函数 唤醒 eventfd
    // EventLoop 中的 epoll 监听到 eventfd 会将 待发送数组中的 [业务 + tcp] 取出, 发送信息
    void wakeup();
    void storeInLoop(Functor&& cb);
    void doPengdingFunctors();
    // END:

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

    // ADD:
    int createEventfd();
    // 读取 eventfd
    void handleRead();
    // END:
    
private:
    // ADD:
    // 用于线程间通信, 即 线程池中的 线程 与 EventLoop 线程通信
    // EventLoop 监听到 新消息, 会调用 Tcp 的 handleMessage 进行处理
    // Tcp 实际上是调用注册在 其中的 回调函数 进行处理
    // 回调函数 先 对消息进行 预处理, 然后将 [消息 + tcp] 放入 线程池的任务队列, 其中 tcp 用于 把 待发送(处理完成)的任务, 传送给 eventloop
    // 线程池 的 子线程 进行 业务处理, 处理完毕后需要 借助 tcp 把 待发送的业务 传递给 EventLoop
    // 其中 tcp 传递 待发送业务 给 EventLoop 其实是在 调用 EventLoop 的 runInLoop 函数, 故 tcp 应包含 eventloop 的 指针/引用
    // runInLoop 函数 将待发送的任务 存入vector, 并唤醒 eventfd(向eventfd写入)
    // EventLoop 中的 evenftd 被 epoll 监听到, eventloop 会 将 待发送任务从 vector 中取出 并 进行发送
    int _evtfd;
    vector<Functor> _pendings;
    MutexLock _mutex;
    // END:

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
