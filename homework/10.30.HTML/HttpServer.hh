#ifndef __HTTPSERVER_HPP__
#define __HTTPSERVER_HPP__


#include <string>
using std::string;

class HttpServer {
public: 
    HttpServer(const string& ip, unsigned short port);
    ~HttpServer();
    void start();
    void recvAndShow();

private:
    string sendHtml();
    string sendPng();

private:
    string _ip;
    unsigned short _port;
    int _fd;
};

#endif
