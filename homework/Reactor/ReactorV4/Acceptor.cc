#include "Acceptor.hh"
#include <asm-generic/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/socket.h>


Acceptor::Acceptor(const string& ip, unsigned short port) 
: _sock()
, _addr(ip, port) { }

Acceptor::~Acceptor() {

}


void Acceptor::ready() {
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}


void Acceptor::setReuseAddr() {
    int reuse = 1;
    int ret = setsockopt(_sock.getfd(), SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    if (ret == -1) {
        perror("setsockopt_addr");
        return ;
    }
}

void Acceptor::setReusePort() {
    int reuse = 1;
    int ret = setsockopt(_sock.getfd(), SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));

    if (ret == -1) {
        perror("setsockopt_port");
        return ;
    }
}

void Acceptor::bind() {
    struct sockaddr_in* paddr = _addr.getInetAddressPtr();
    int ret = ::bind(_sock.getfd(), reinterpret_cast<struct sockaddr*>(paddr), sizeof(struct sockaddr_in));

    if (ret == -1) {
        perror("bind");
        return ;
    }
}

void Acceptor::listen() {
    int ret = ::listen(_sock.getfd(), 1024);

    if (ret == -1) {
        perror("listen");
        return ;
    }
}

int Acceptor::accept() {
    // 第 2/3 参数 用于 获取 客户端 的 ip/port 的信息
    // 打印消息 不在此处打印, 故直接填 nullptr
    int fd = ::accept(_sock.getfd(), nullptr, nullptr);

    if (fd == -1) {
        perror("accept");
        return -1;
    }

    return fd;
}

int Acceptor::getListenFd() {
    return _sock.getfd();
}
