#include <asm-generic/socket.h>
#include <bits/sockaddr.h>
#include <arpa/inet.h>
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return -1;
    }

    int reuse = 1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &reuse, sizeof(reuse));
    if (ret == -1) {
        close(sockfd);
        perror("setsockopt");
        return -1;
    }


    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    ret = bind(sockfd, (sockaddr*) &addr, sizeof(addr));
    if (ret == -1) {
        close(sockfd);
        perror("bind");
        return -1;
    }

    ret = listen(sockfd, 1024);
    if (ret == -1) {
        close(sockfd);
        return -1;
    }

    sockaddr_in addr1;
    socklen_t size = sizeof(addr1);
    int connfd = accept(sockfd, (sockaddr*) &addr1, &size);
    cout << "connected!" << endl;

    while (1) {
        char buf[1024] = {0};
        int ret = recv(connfd, buf, sizeof(buf), 0);
        cout << "Message: " << buf;
    }

    return 0;
}




