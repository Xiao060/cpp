#include "Acceptor.hh"
#include "TcpConnection.hh"
#include <iostream>
#include <unistd.h>

using std::cin;
using std::cout;
using std::endl;




int main(int argc, char* argv[]) {

    Acceptor acceptor("127.0.0.1", 1234);
    acceptor.ready();

    TcpConnection tcp(acceptor.accept());

    while (1) {
        string str = tcp.receive();
        cout << str;
        tcp.send("hello " + str);
    }

    return 0;
}




