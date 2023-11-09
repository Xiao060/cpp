#include <iostream>



#include <workflow/WFFacilities.h>
#include <wfrest/HttpMsg.h>
#include <wfrest/HttpServer.h>


using std::cin;
using std::cout;
using std::endl;

WFFacilities::WaitGroup waitGroup(1);


void getHandler(const wfrest::HttpReq* req, wfrest::HttpResp* resp) {

    resp->File("postform.html");


}


int main(int argc, char* argv[]) {

    wfrest::HttpServer httpServer;

    httpServer.GET("/login", getHandler);

    if (httpServer.start(8888) == 0) {
        waitGroup.wait();
    }

    return 0;
}




