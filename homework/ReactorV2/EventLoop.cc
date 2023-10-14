#include "EventLoop.hh"
#include "Acceptor.hh"
#include "TcpConnection.hh"
#include <algorithm>
#include <asm-generic/errno-base.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <sys/epoll.h>
#include <unistd.h>
#include <utility>
#include <vector>


using std::cout;
using std::endl;
using std::make_pair;


EventLoop::EventLoop(Acceptor& acceptor) 
: _epfd(createEpollFd())
, _evtList(1024)
, isLooping(false) 
, _acceptor(acceptor) { 

    // Acceptor 中的 包含 两个子对象
    // 1. Socket, 此 socket 其实是服务端 最初的通信sock, 被acceptor变为 监听sock 
    // 2. InetAddress, 储存 服务端的 ip/port 信息
    int listenfd = acceptor.getListenFd();
    addEpollReadFd(listenfd);
}

EventLoop::~EventLoop() {
    close(_epfd);
}


int EventLoop::createEpollFd() {
    int epfd = epoll_create(1);

    if (epfd == -1) {
        perror("epoll_create") ;
        return -1;
    }

    return epfd;
}

void EventLoop::addEpollReadFd(int fd) {

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = fd;    

    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &event);

    if (ret == -1) {
        perror("epoll_ctl_addEpollReadFd");
        return ;
    }
}

void EventLoop::delEpollReadFd(int fd) {

    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, nullptr);

    if (ret == -1) {
        perror("epoll_ctl_delEpollReadFd");
        return ;
    }
} 

void EventLoop::waitEpollFd() {

    int nums = 0;

    // 使用 do-while 循环, 保证 epoll_wait 能够完整执行
    // 此处 epoll_event 数组最多储存 1024 个 事件, 多余的事件下次处理 (epoll 水平触发)
    // 次处 使用 vector 模拟数组, vector 首地址 -----> begin迭代器解引用 然后取地址
    do {
        nums = epoll_wait(_epfd, &*_evtList.begin(), _evtList.size(), 3000);
    } while (nums == -1 && errno == EINTR);

    if (nums == -1) {
        perror("epoll_wait");
        return ;
    }

    if (nums == 0) {
        cout << ">>epoll_wait timeout!!!" << endl;
        return ;
    }

    // 若 就绪fd 数量 等于 vector 上限, 则 意味着可能 就绪数量 > vector上限, 需要扩容
    if (nums == _evtList.size()) {
        _evtList.resize(2 * _evtList.size());
    }

    for (int i = 0; i < nums; ++i) {

        int fd = _evtList[i].data.fd;

        if (fd == _acceptor.getListenFd()) {
            handleNewConnection();
            continue;
        }

        // 若 监听的事件 有多种, 则需要判断 事件类型 
        // 此处因为 只监听 epollin 事件, 故舍弃判断
        // if (_evtList[i].events & EPOLLIN) 

        handleMessage(fd);
    }
}

// 用于启动 epoll_wait
void EventLoop::loop() {
    isLooping = true;
    while (isLooping) {
        waitEpollFd();
    }
}

// 用于结束 epoll_wait
void EventLoop::unloop() {
    isLooping = false;
}


// 初始化 3 个 cb 成员变量
void EventLoop::setNewConnectionCallback(TcpConnectionCallback&& cb) {
    _onNewConnectionCb = std::move(cb);
}

void EventLoop::setMessageCallback(TcpConnectionCallback&& cb) {
    _onMessageCb = std::move(cb);
}

void EventLoop::setCloseCallback(TcpConnectionCallback&& cb) {
    _onMessageCb = std::move(cb);
}


// 处理新的连接
// 1. 调用 链接器 建立新连接 (获取 新的文件描述符)
// 2. 将 fd 加入 epoll 监听
// 3. 为 新fd 建立 真正的 tcp连接
// 4. 把 fd:tcp 加入 map
// 5. 注册回调函数
// 6. 调用 tcp 的 _onNewConnectionCb 函数
void EventLoop::handleNewConnection() {
    int fd = _acceptor.accept();

    if (fd == -1) {
        perror("handleNewConnection");
        return ;
    }

    addEpollReadFd(fd);
    TcpConnectionPtr pTcp(new TcpConnection(fd));

    pTcp->setNewConnectionCallback(_onNewConnectionCb);
    pTcp->setMessageCallback(_onMessageCb);
    pTcp->setCloseCallback(_onCloseCb);

    _conns.insert(make_pair(fd, pTcp));

    pTcp->handleNewConnectionCallback();
}

void EventLoop::handleMessage(int fd) {

    // 需要 获取 fd 对应的 tcp 进行实际通信
    // 判断 连接是否 关闭
    // 如果 recv 接收数量为 0, 即 连接关闭
    // 则 需要 从map中 删除对应 pair, 将 pair 移除监听, 并调用 tcp 的 _onCloseConnectionCb 函数
    // 否则 调用 tcp 的 _onMessageConnectionCb 函数

    // 正常情况下 fd 肯定存在 _conns map 中, 但是建议 增加 检测机制, 增强代码健壮性
    auto iter = _conns.find(fd);

    if (iter == _conns.end()) {
        cout << ">>This connection is not exit!" << endl;
        return ;
    }

    // shared_ptr<TcpConnection> spTcp = _conns[fd];
    shared_ptr<TcpConnection> spTcp = iter->second;
    bool isClose = spTcp->isClosed();

    if (isClose) {
        spTcp->handleCloseCallback();
        delEpollReadFd(fd);
        // _conns.erase(fd);
        _conns.erase(iter);
    } else {
        spTcp->handleMessageCallback();
    }
}
