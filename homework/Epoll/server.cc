#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>


using std::cin;
using std::cout;
using std::endl;

#define SIZE(arry) (sizeof(arry) / sizeof(arry[0]))


// 服务端
// 1. sockfd() 建立 通信socket
// 2. setsockopt() 设置 ip/port 复用
// 3. bind() 绑定 ip/port
// 4. listen() 将 通信socket 转变为 监听socket
// 5. accept() 从 监听socket 的全连接队列 取出一个连接, 建立 通信socket
// 6. recv/send 
// 7. close()

int main(int argc, char* argv[]) {

    // 1. 建立通信 socket
    // 返回值: sockfd
    // 参数 1: domain, 即 IP 版本: AF_INET (ipv4) / AF_INET6 (ipv6)
    // 参数 2: type, 即 传输层类型: SOCK_STREAM (TCP) / SOCK_DGRAM (UDP)
    // 参数 3: protocol, 即 传输层协议: 填 0, 根据前两项自动选择
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return -1;
    }

    // 2. 设置 ip/port 复用
    // 参数 2: 协议层: SOL_SOCKET / ...
    // 参数 3: 要设置的 选项名称: SO_REUSEADDR / SO_REUSEPORT
    // 参数 4: 要设置的 选项值 的地址: 设置 ip/port 复用, 选项值 为一个整数
    // 参数 5: 选项值的 长度:
    int reuse = 1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if (ret == -1) {
        perror("setsockopt_reuseaddr");
        close(sockfd);
        return -1;
    }

    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
    if (ret == -1) {
        perror("setsockopt_reuseaddr");
        close(sockfd);
        return -1;
    }

    // 3. 绑定 ip/port
    // 参数 2: struct sockaddr 的 指针, 指向 struct sockaddr_in 结构体
    //         struct sockaddr_in 结构体, 内含 ip版本 / ip / port 信息; 
    //         其中 port 采用 网络字节序, 即大端存储
    //         使用时需要先取地址, 再强转成 struct sockaddr 的 指针
    //         
    // 参数 3: struct sockaddr_in 结构体的 长度
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    ret = bind(sockfd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
    if (ret == -1) {
        perror("bind");
        close(sockfd);
        return -1;
    }

    // 4. 将 通信socket 转变为 监听socket
    // 参数 2: 全连接队列的长度
    ret = listen(sockfd, 1024);
    if (ret == -1) {
        perror("listen");
        close(sockfd);
        return -1;
    }

    cout << "listening..." << endl;

    // 使用 epoll 完成 IO 多路复用
    // 本质是 创建一个文件对象, 对象内部 维护 2 个集合, 即 监听/就绪 集合
    // 监听集合 底层采用 红黑树 实现, 就绪集合 采用 线性表 实现
    // 参数 1: 为任意正整数, 无意义
    // 返回值: epoll 文件对象的 文件描述符
    int epfd= epoll_create(1);
    if (epfd == -1) {
        perror("epoll_create");
        return -1;
    }

    // 往 epoll 文件对象 的监听集合内 添加/删除 文件描述符
    // 参数 2: 对 就绪集合 的操作,  EPOLL_CTL_ADD / EPOLL_CTL_DEL / EPOLL_CTL_MOD
    // 参数 3: 需要 添加/删除 的 文件描述符
    // 参数 4: 参数 3 就绪时 返回的 内容, 即 struct epoll_event 结构体
    // 结构体 第1项 events, 就绪条件: EPOLLIN / EPOLLOUT / EPOLLERR / EPOLLET (按位或)
    // 结构体 第2项 data 为 union, 通常返回 fd;
    struct epoll_event event;

    event.events = EPOLLIN;
    event.data.fd = sockfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
    if (ret == -1) {
        perror("epoll_ctl");
        return -1;
    }

    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    if (ret == -1) {
        perror("epoll_ctl");
        return -1;
    }

    char ip[1024];
    char buf[1024];

    struct epoll_event events[1024];
    while (1) {
        bzero(events, sizeof(events));
        int nums = epoll_wait(epfd, events, SIZE(events), -1);
        if (nums == -1) {
            perror("epoll_wait");
            return -1;
        }

        for (int i = 0; i < nums; ++i) {
            
            // 需要通过 按位与 判断 事件类型
            // but 此处 监听事件 只有 EPOLLIN, 可省略 判断部分
            // if (events[i].events & EPOLLIN) { }
            int fd = events[i].data.fd;

            if (fd == sockfd) {
                struct sockaddr_in addr;
                socklen_t addLen  = sizeof(addr);
                int fd = accept(sockfd, reinterpret_cast<struct sockaddr*>(&addr), &addLen);
                if (fd == -1) {
                    perror("accept");
                    return -1;
                }

                // 打印连接成功的消息
                // ip 地址需要使用 inet_ntop 进行转换为 字符串
                // 参数 1: ip 协议 
                // 参数 2: struct sockaddr_in 中的 ip 项的地址
                // 参数 3: 字符串 地址
                // 返回值: 字符串 地址
                bzero(ip, sizeof(ip));
                inet_ntop(AF_INET, &addr.sin_addr.s_addr, ip, sizeof(ip));

                cout << "receive connection from " << ip << ":" << ntohs(addr.sin_port) << endl;

                event.events = EPOLLIN;
                event.data.fd = fd;
                int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
                if (ret == -1) {
                    perror("epoll_ctl");
                    return -1;
                }

                continue;
            }

            if (fd == STDIN_FILENO) {
                bzero(buf, sizeof(buf));
                read(fd, buf, sizeof(buf));
                continue;
            }

            bzero(buf, sizeof(buf));
            int recvNum = recv(fd, buf, sizeof(buf), 0);
            if (recvNum == 0) {
                close(fd);
                epoll_ctl(epfd, EPOLL_CTL_DEL, fd, nullptr);
                cout << "fd = " << fd << " quit!" << endl;
                continue;
            }
            cout << "client: " << buf; 
        }
    }

    return 0;
}




