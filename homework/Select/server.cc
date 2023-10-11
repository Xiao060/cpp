#include <iostream>
#include <sys/socket.h>



using std::cin;
using std::cout;
using std::endl;



// 服务端
// 1. sockfd() 建立 通信socket
// 2. setsockopt() 设置 ip/port 复用
// 3. bind() 绑定 ip/port
// 4. listen() 将 通信socket 转变为 监听socket
// 5. accept() 从 监听socket 的全连接队列 取出一个连接, 建立 通信socket
// 6. recv/send 
// 7. close()

int main(int argc, char* argv[]) {

    int sockfd = socket(, , );
    

    return 0;
}




