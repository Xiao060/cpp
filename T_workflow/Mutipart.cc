#include <iostream>

#include "MutipartUpload.hh"


using std::cin;
using std::cout;
using std::endl;




int main(int argc, char* argv[]) {

    MultipartUpload uploadServer(1);
    uploadServer.start(8888);
    

    return 0;
}




