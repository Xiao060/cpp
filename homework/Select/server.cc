#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

const int  FDSIZE = 1024; 

using std::cout;
using std::endl;

// 服务端
// 1. sockfd() 建立 通信socket
// 2. setsockopt() 设置 ip/port 复用
// 3. bind() 绑定 ip/port
// 4. listen() 将 通信socket 转变为 监听socket
// 5. accept() 从 监听socket 的全连接队列 取出一个连接, 建立 通信socket
// 6. recv/send or read/write 
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

    // 设置 监听集合
    fd_set rdset, allset;
    FD_ZERO(&rdset);
    FD_ZERO(&allset);
    FD_SET(sockfd, &allset);
    FD_SET(STDIN_FILENO, &allset);

    int maxfd = sockfd;

    int fds[FDSIZE];
    memset(fds, -1, sizeof(fds));
    int maxIdx = -1;

    // ip 储存 连接之后, 使用 inet_ntop 转换成的 字符串ip
    char ip[1024];
    // buf 储存 从客户端 接收的内容
    char buf[1024];

    while (1) {
        rdset = allset;
        int nums = select(maxfd + 1, &rdset, nullptr, nullptr, nullptr);

        if (nums == -1) {
            perror("select");
            close(sockfd);
            return -1;
        }

        if (FD_ISSET(sockfd, &rdset)) {

            // 5. 从 监听socket 的 全连接队列 取出一个连接 建立 通信socket
            // 参数 2: struct sockaddr 的指针, 指向 struct sockaddr_in 结构体, 为 传入传出参数
            // 参数 3: struct sockaddr 长度的 地址
            struct sockaddr_in addr;
            bzero(&addr, sizeof(addr));
            socklen_t addrLen = sizeof(addr);

            int fd = accept(sockfd, reinterpret_cast<struct sockaddr*>(&addr), &addrLen);
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

            // 将新连接的 通信socket 加入 监听队列, 放入 fd数组, 并 更新 maxfd/maxIdx
            int i;
            for (i = 0; i < FDSIZE; ++i) {
                if (fds[i] == -1) {
                    fds[i] = fd;
                    maxIdx = (i > maxIdx) ? i : maxIdx;
                    maxfd = (fd > maxfd) ? fd : maxfd;

                    FD_SET(fd, &allset);
                    break;
                }
            }

            if (i == FDSIZE) {
                perror("to many connection...");
                return -1;
            }

            --nums;
        }

        if (FD_ISSET(STDIN_FILENO, &rdset)) {
            bzero(buf, sizeof(buf));
            read(STDIN_FILENO, buf, sizeof(buf));

            for (int i = 0; i <= maxIdx; ++i) {
                if (fds[i] >= 0) {
                    send(fds[i], buf, strlen(buf), 0);
                }
            }

            --nums;
        }

        if (!nums) {
            continue;
        }

        for (int i = 0; i <= maxIdx; ++i) {

            if (fds[i] >= 0 && FD_ISSET(fds[i], &rdset)) {

                int fd = fds[i];

                bzero(buf, sizeof(buf));
                int recvNums = recv(fd, buf, sizeof(buf), 0);

                if (recvNums == 0) {
                    close(fd);
                    FD_CLR(fd, &allset);
                    fds[i] = -1;
                } else {
                    cout << "client: " << buf;
                }

                --nums;
                if (!nums) {
                    break;
                }
            }
        }
    }


    for (int i = 0; i < FDSIZE; ++i) {
        if (fds[i] >= 0) {
            close(fds[i]);
            fds[i] = -1;
        }
    }

    close(sockfd);

    return 0;
}




