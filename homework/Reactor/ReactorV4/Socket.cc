#include "Socket.hh"
#include <cstdio>
#include <sys/socket.h>
#include <unistd.h>


Socket::Socket() {
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (_sockfd == -1) {
        perror("socket");
        return ;
    }
}

Socket::Socket(int sockfd) 
: _sockfd(sockfd) {

}

Socket::~Socket() {
    close(_sockfd);
}

int Socket::getfd() const {
    return _sockfd;
}