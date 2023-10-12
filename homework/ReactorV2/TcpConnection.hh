#ifndef __TCPCONNECTION_HPP__
#define __TCPCONNECTION_HPP__

#include "InetAddress.hh"
#include "Socket.hh"
#include "SocketIO.hh"



class TcpConnection {

public:
    TcpConnection();
    
    
    
private:
    Socket _conn;    
    SocketIO _socketIO;
    InetAggress _localAddr;
    InetAggress _peerAddr;
};

#endif
