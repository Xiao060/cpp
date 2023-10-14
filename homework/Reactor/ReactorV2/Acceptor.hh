#ifndef __ACCEPTOR_HPP__
#define __ACCEPTOR_HPP__

#include "InetAddress.hh"
#include "Socket.hh"


class Acceptor {

public:
    Acceptor(const string& ip, unsigned short port);
    ~Acceptor();

    void ready();

private:
    void setReuseAddr();
    void setReusePort();
    void bind();
    void listen();
    
public:
    int accept();
    int getListenFd();
    
private:
    Socket _sock;
    InetAddress _addr;
};

#endif
