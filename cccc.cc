#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>


#define LISTENQ 5


std::string read_image(const std::string& image_path);
int send_image(int & fd, std::string& image);
int main(){
    int listenfd, connfd;
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0){
        std::cout << "create socketfd failed" <<std::endl;
        return 0;
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.23.133"); 
    servaddr.sin_port = htons(8888);
    
    int bind_ok = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if(bind_ok < 0){
        std::cout << "bind socket with server address  failed" <<std::endl;
        return 0;
    }
    
    int listen_ok = listen(listenfd, LISTENQ);
    if(listen_ok < 0){
        std::cout << "listen socket  failed" <<std::endl;
        return 0;
    }

    std::string img = read_image("lin.png");
    int write_ok;
    while(1){
        connfd = accept(listenfd, NULL, NULL);
        if(connfd < 0){
            std::cout << "create connection socket failed" <<std::endl;
            return 0;
        }

        write_ok = send_image(connfd, img);
        if(write_ok < 0){
            std::cout << "write info to connection socket failed" <<std::endl;
            close(connfd);
            return 0;
        }
        close(connfd);
    }
}

std::string read_image(const std::string& image_path){
    std::ifstream is(image_path.c_str(), std::ifstream::in);
    is.seekg(0, is.end);
    int flength = is.tellg();
    is.seekg(0, is.beg);
    char * buffer = new char[flength];
    is.read(buffer, flength);
    std::string image(buffer, flength);
    return image;
}

int send_image(int & fd, std::string& image){
	 // 创建响应实体
    int body_length = image.size();
    const char * body = image.data();
    int response_length = body_length;
    char * buffer = new char[response_length];
    memcpy(buffer, body, body_length);
    // 将响应写入发送缓冲区，并发送
    int ret = write(fd, buffer, response_length);
	 // 清理
    delete [] buffer;
    return ret;
}
