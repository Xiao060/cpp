#include "HttpServer.hh"
#include <iostream>



int main(int argc, char* argv[]) {

    HttpServer http("192.168.23.133", 8888);

    http.start();
    http.recvAndShow(); 

    return 0;
}




