#include "HttpServer.hh"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;




int main(int argc, char* argv[]) {

    HttpServer http("192.168.23.133", 8888);

    http.start();
    http.recvAndShow(); 

    return 0;
}




