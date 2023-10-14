#ifndef __SOCKETIO_HPP__
#define __SOCKETIO_HPP__

class SocketIO {

public:
    SocketIO(int connfd);
    ~SocketIO();

    int readn(char* buf, int len);
    int readLine(char* buf, int len);

    int write(const char* buf, int len);
    
private:
    int _connfd; 
};

#endif
