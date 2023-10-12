#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

using std::cout;
using std::endl;

// #define SIZE2(arry) (sizeof(arry) / sizeof(arry[0]))

template <typename T>
inline int SIZE(T& array) {
    return sizeof(array) / sizeof(array[0]);
}

// 客户端
// 1. sockfd() 建立 通信socket
// 2. connect() 与 服务端 建立连接
// 3. recv/send 
// 4. close()


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

    // 2. 与 服务端 建立连接
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

    int ret = connect(sockfd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr));
    if (ret == -1) {
        perror("connect");
        close(sockfd);
        return -1;
    }


    // 使用 epoll 完成 IO 多路复用
    // 本质是 创建一个文件对象, 对象内部 维护 2 个集合, 即 监听/就绪 集合
    // 监听集合 底层采用 红黑树 实现, 就绪集合 采用 线性表 实现
    // 参数 1: 为任意正整数, 无意义
    // 返回值: epoll 文件对象的 文件描述符
    int epfd = epoll_create(1);
    if (epfd == -1) {
        perror("epoll_create");
        close(sockfd);
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
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);

    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);


    char buf[1024];
    struct epoll_event events[1024];
    while (1) {
        bzero(events, sizeof(events));

        // 内核轮询, 用户等待
        // 参数 2: struct epoll_event 的数组
        // 当 epoll 文件对象 监听集合(红黑树) 中的 fd 就绪时 将其注册的 struct epoll_event 移入到 epoll 文件对象的 就绪集合(双链表) 内
        // 轮询结束, 将 epoll 文件对象 的 就绪集合(内核态) 拷贝到 用户态数组 中去
        // 参数 3: 数组长度
        // 参数 4: 超时时间, -1 为永久等待
        int nums = epoll_wait(epfd, events, SIZE(events), -1);

        for (int i = 0; i < nums; ++i) {

            // 需要通过 按位与 判断 事件类型
            // but 此处 监听事件 只有 EPOLLIN, 可省略 判断部分
            // if (events[i].events & EPOLLIN) { }

            int fd = events[i].data.fd;

            if (fd == sockfd) {
                bzero(buf, sizeof(buf));
                int recvNums = recv(fd, buf, sizeof(buf), 0);
                if (recvNums == 0) {
                    cout << "server quit!" << endl;
                    close(sockfd);
                    return -1;
                }
                cout << buf;
                continue;
            }
            

            bzero(buf, sizeof(buf));
            read(fd, buf, sizeof(buf));
            send(sockfd, buf, strlen(buf), 0);
        }



    }
    
    

    return 0;
}




