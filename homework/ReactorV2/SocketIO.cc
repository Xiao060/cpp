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

        // 此处 直接返回 已读取的字符数量
        // teacher 返回的是  len - ret, 即 len + 1, 用于区分是否读取失败
        if (ret == -1) {
            perror("recv_readn");
            break;
            // return len - left;
        }

        if (ret == 0) {
            break;
        }

        left -= ret;
        pstr += ret;
    }

    return len - left;
}

int SocketIO::readLine(char* buf, int len) {

    int left = len - 1;
    char* pstr = buf;
    int total = 0;

    while (len > 0) {
        int ret = recv(_connfd, buf, len, MSG_PEEK);
    
        if (ret == -1 && errno == EINTR) {
            continue;
        }

        if (ret == -1) {
            perror("recv_readLine");
            return -1;
        }

        if (ret == 0) {
            break;
        }

        for (int i = 0; i < ret; ++i) {

            if (buf[i] == '\n') {
                readn(buf, i+1);
                buf[i+1] = '\0';

                return total + i + 1;
            }
        }

        total += ret;
        pstr += ret;
    }


    
}


int SocketIO::write(const char* buf, int len) {

}
