#include "EchoServer.hh"

int main(int argc, char* argv[]) {

    EchoServer echoServer(4, 10, "127.0.0.1", 1234);
    echoServer.start();

    return 0;
}




