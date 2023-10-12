#include "SocketIO.hh"
#include <asm-generic/errno-base.h>
#include <cstdio>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>



SocketIO::SocketIO(int connfd) 
: _connfd(connfd) { }

SocketIO::~SocketIO() { 
    close(_connfd);
}


// 读取 n 个 字符, 返回值为 最终读取的 字符数量
int SocketIO::readn(char* buf, int len) {

    int left = len;
    char * pstr = buf;

    while (left > 0) {
        int ret = recv(_connfd, pstr, len, 0);

        if (ret == -1 && errno == EINTR) {
            continue;
        } 

        if (ret == -1) {
            perror("recv");
            return 
        }

    }



}

int SocketIO::readLine(char* buf, int len) {

}


int SocketIO::write(const char* buf, int len) {

}
