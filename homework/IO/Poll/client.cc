#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using std::cin;
using std::cout;
using std::endl;

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

    
    

    return 0;
}




