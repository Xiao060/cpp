#include <asm-generic/socket.h>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <ostream>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "HttpServer.hh"
#include <cstring>
#include <sys/stat.h>

using std::cout;
using std::endl;

HttpServer::HttpServer(const string& ip, unsigned short port) 
: _ip(ip) 
, _port(port) 
, _fd(-1) { }


HttpServer::~HttpServer() {
    if (_fd > -1) {
        close(_fd);
    }
}


void HttpServer::start() {

    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if (_fd == -1) {
        perror("socket");
        return;
    }

    int reuse = 1;
    int ret = setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &reuse, sizeof(reuse));
    if (ret == -1) {
        perror("setsockopt");
        return;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    addr.sin_addr.s_addr = inet_addr(_ip.c_str());

    ret = bind(_fd, (sockaddr*) &addr, sizeof(addr));
    if (ret == -1) {
        perror("bind");
        return;
    }

    ret = listen(_fd, 1024);
    if (ret == -1) {
        perror("listen");
        return;
    }
}


void HttpServer::recvAndShow() {
    sockaddr_in addr;
    socklen_t len = sizeof(addr);
    int fd = accept(_fd, (sockaddr*) &addr, &len);
    cout << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << " has connected!" << endl;

    while (1) {
        char buf[1024] = {0};
        read(fd, buf, sizeof(buf));
        cout << buf;

        if (strstr(buf, "GET / HTTP/1.1")) {
            string tmp = sendHtml();
            write(fd, tmp.c_str(), tmp.size());
        } else if (strstr(buf, "GET /lin.jpg HTTP/1.1")) {
            sendPng(fd);
        } else if (strstr(buf, "GET /favicon.ico HTTP/1.1")) {
            sendPng(fd);
        }
    }
}

string HttpServer::sendHtml() {
    string firstLine = "HTTP/1.1 200 OK\r\n";

    string body = "<html><body><img src=\"./lin.jpg\" alt=\"Pulpit rock\" width=\"461\" height=\"712\"></body></html>";

    string emptyLine("\r\n");

    string headers = "Server: Cloudisk Server1.0\r\n";
    headers += "Content-Type: text/html\r\n";
    headers += "Content-Length: " + std::to_string(body.size()) + "\r\n"; 

    return firstLine + headers + emptyLine + body;
}



void HttpServer::sendPng(int fd) {

    int f = open("lin.jpg", 2);
    struct stat statbuf;
    fstat(f,&statbuf);
    int size=statbuf.st_size;

    string firstLine = "HTTP/1.1 200 OK\r\n";
    string emptyLine("\r\n");

    string headers = "Server: Cloudisk Server1.0\r\n";
    headers += "Content-Type: image/jpeg\r\n";
    headers += "Content-Length: " + std::to_string(size) + "\r\n"; 

    string head = firstLine + headers + emptyLine;

    write(fd, head.c_str(), head.size());

    while (1) {
        char buf[4096] = {0};
        int ret = read(f, buf, sizeof(buf));
        if (ret == 0) {
            break;
        }

        write(fd, buf, ret);
    }
}
