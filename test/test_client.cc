#include <bits/sockaddr.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <cstring>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return -1;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = connect(sockfd, (sockaddr*) &addr, sizeof(addr));
    if (ret == -1) {
        close(sockfd);
        perror("connect");
        return -1;
    }

    while (1) {
        char buf[1024] = {0};
        read(STDIN_FILENO, buf, sizeof(buf));
        int ret = send(sockfd, buf, strlen(buf), 0);
    }

    return 0;
}




