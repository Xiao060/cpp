#include <cstdio>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


using std::cin;
using std::cout;
using std::endl;



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
    // 参数 2: struct sockaddr_in 结构体, 内含 ip版本 / ip / port 信息; 
    //         其中 port 采用 网络字节序, 即大端存储
    //         使用时需要先取地址, 再强转成 struct sockaddr 的 指针
    //         
    // 参数 3: struct sockaddr_in 结构体的指针

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



    

    

    return 0;
}




