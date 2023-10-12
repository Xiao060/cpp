#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

class Socket {

public:
    Socket();
    explicit Socket(int sockfd);
    ~Socket();
    int getfd() const;
    
private:
    int _sockfd;
};

#endif