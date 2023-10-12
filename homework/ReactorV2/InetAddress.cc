#include "InetAddress.hh"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>



InetAggress::InetAggress(const string& ip, unsigned short port) {
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
    _addr.sin_port = htons(port);
}

InetAggress::InetAggress(const struct sockaddr_in& addr) 
: _addr(addr) { }

InetAggress::~InetAggress() {

}


string InetAggress::getIp() {
    char buf[1024] = {0};
    inet_ntop(AF_INET, &_addr.sin_addr.s_addr, buf, sizeof(buf));
    return buf;
}

unsigned short InetAggress::getPort() {
    return ntohs(_addr.sin_port);
}

struct sockaddr_in* InetAggress::getInetAddressPtr() {
    return &_addr;
}



