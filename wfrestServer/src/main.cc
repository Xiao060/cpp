#include "CloudiskServer.hh"


#include <csignal>
#include <functional>
#include <iostream>
#include <unistd.h>



using std::cin;
using std::cout;
using std::endl;
using std::bind;
using namespace std::placeholders;



int main(int argc, char* argv[]) {

    CloudiskServer Server(1);
    // signal(SIGINT, &CloudiskServer::handler);

    Server.loadStaticResourceModule();
    Server.loadUserRegisterModule();
    Server.loadUserLoginModule();
    Server.loadUserInfoModule();
    Server.start(8888);



    return 0;
}




