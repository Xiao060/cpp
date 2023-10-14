#include "InetAddress.hh"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>



InetAddress::InetAddress(const string& ip, unsigned short port) {
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
    _addr.sin_port = htons(port);
}

InetAddress::InetAddress(const struct sockaddr_in& addr) 
: _addr(addr) { }

InetAddress::~InetAddress() {

}


string InetAddress::getIp() {
    char buf[1024] = {0};
    inet_ntop(AF_INET, &_addr.sin_addr.s_addr, buf, sizeof(buf));
    return buf;
}

unsigned short InetAddress::getPort() {
    return ntohs(_addr.sin_port);
}

struct sockaddr_in* InetAddress::getInetAddressPtr() {
    return &_addr;
}



