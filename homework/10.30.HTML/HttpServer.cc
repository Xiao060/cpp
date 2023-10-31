#include <asm-generic/socket.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <openssl/http.h>
#include <ostream>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "HttpServer.hh"

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

    while (1) {
        sockaddr_in addr;
        socklen_t len = sizeof(addr);
        int fd = accept(_fd, (sockaddr*) &addr, &len);
        cout << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port) << " has connected!" << endl;
        
        char buf[1024] = {0};
        read(fd, buf, sizeof(buf));
        cout << buf;

        string tmp = sendHtml();
        write(fd, tmp.c_str(), tmp.size());


        bzero(buf, sizeof(buf));
        read(fd, buf, sizeof(buf));
        cout << buf;

        string img = sendPng();
        write(fd, img.data(), img.size());

        close(fd);
    }
}

string HttpServer::sendHtml() {
    string firstLine = "HTTP/1.1 200 OK\r\n";

    string body = "<html><body><img src=\"./lin.jpg\" alt=\"Pulpit rock\" width=\"304\" height=\"228\"></body></html>";

    string emptyLine("\r\n");

    string headers = "Server: Cloudisk Server1.0\r\n";
    headers += "Content-Type: text/html\r\n";
    headers += "Content-Length: " + std::to_string(body.size()) + "\r\n"; 

    return firstLine + headers + emptyLine + body;
}



string HttpServer::sendPng() {
    string firstLine = "HTTP/1.1 200 OK\r\n";

    string body;
    std::ifstream ifs("lin.png");
    ifs >> body; 

    string emptyLine("\r\n");

    string headers = "Server: Cloudisk Server1.0\r\n";
    headers += "Content-Type: text/jpeg\r\n";
    headers += "Content-Length: " + std::to_string(body.size()) + "\r\n"; 

    return firstLine + headers + emptyLine + body;
}
