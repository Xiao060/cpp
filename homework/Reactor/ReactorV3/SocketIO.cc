#include "SocketIO.hh"
#include "InetAddress.hh"
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


int SocketIO::readn(char* buf, int len) {

    // 此处 使用 do_while 循环来处理 中断的问题, 保证能进行一次完整的 recv
    // 使用 do-while 使 后续代码 减少一层缩进, 可读性更强, 更美观
    int ret = 0;
    do {
        ret = recv(_connfd, buf, len, MSG_WAITALL);
    } while (ret == -1 && errno == EINTR);

    if (ret == -1) {
        perror("recv_readn");
        return -1;
    }

    return 0;

    /*************************************************************************************************/
    /*
    while (1) {
        int ret = recv(_connfd, buf, len, MSG_WAITALL);

        if (ret == -1 && errno == EINTR) {
            continue;
        }

        if (ret == -1) {
            perror("recv_readn");
            return -1;
        }

        return 0;
    }
    */

    /*************************************************************************************************/
    /*
    // 读取 n 个 字符, 返回值为 最终读取的 字符数量
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
    */
}




int SocketIO::readLine(char* buf, int len) {

    int left = len - 1;
    int total = 0;

    while (len > 0) {
        int ret = recv(_connfd, buf, left, MSG_PEEK);
    
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
                readn(buf, total + i + 1);
                buf[i+1] = '\0';

                return total + i + 1;
            }
        }

        total += ret;
        left -= ret;
    }

    buf[total] = '\0';
    return total;
}


int SocketIO::write(const char* buf, int len) {

    // 此处 使用 do_while 循环来处理 中断的问题, 保证能进行一次完整的 send
    // 使用 do-while 使 后续代码 减少一层缩进, 可读性更强, 更美观
    int ret = 0;
    do {
        ret = send(_connfd, buf, len, 0);
    } while (ret == -1 && errno == EINTR);

    if (ret == -1) {
        perror("send_write");
        return -1;
    }

    return 0;

    /**********************************************************************************************/
    /*
    while (1) {
        int ret = send(_connfd, buf, len, 0);
    
        if (ret == -1 && errno == EINTR) {
            continue;
        }

        if (ret == -1) {
            perror("send");
            return -1;
        }

        return 0;
    }
    */
}
