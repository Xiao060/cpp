#ifndef __INETAGGRESS_HPP__
#define __INETAGGRESS_HPP__

#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>

using std::string;


class InetAddress {

public:
    InetAddress(const string& ip, unsigned short port);
    InetAddress(const struct sockaddr_in& addr);
    ~InetAddress();

    string getIp();
    unsigned short getPort();
    struct sockaddr_in* getInetAddressPtr();
    
private:
    struct sockaddr_in _addr;    
};

#endif
