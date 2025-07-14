#include <iostream>
#include <string>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "Buffer.h"


using namespace std;

int main() {
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd == -1) {
        perror("创建socket失败");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.40.129");
    addr.sin_port = htons(1234);
    int ret = ::connect(sockfd,(sockaddr*)&addr,sizeof(addr));
    if(ret == -1){
        perror("连接服务端失败");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    Buffer* sendBuffer = new Buffer();
    Buffer* readBuffer = new Buffer();
    
    while(true){
        std::string input;
        std::getline(std::cin, input);
        sendBuffer->clear();
        sendBuffer->append(input.c_str(), input.size());
        ssize_t write_bytes = ::write(sockfd, sendBuffer->c_str(), sendBuffer->size());
        if(write_bytes == -1){
            printf("socket already disconnected, can't write any more!\n");
            break;
        }
        int already_read = 0;
        char buf[1024];    //这个buf大小无所谓
        while(true){
            memset(&buf, 0, sizeof(buf));
            ssize_t read_bytes = ::read(sockfd, buf, sizeof(buf));
            if(read_bytes > 0){
                readBuffer->append(buf, read_bytes);
                already_read += read_bytes;
            } else if(read_bytes == 0){         //EOF
                printf("server disconnected!\n");
                exit(EXIT_SUCCESS);
            }
            if(already_read >= sendBuffer->size()){
                printf("message from server: %s\n", readBuffer->c_str());
                break;
            } 
        }
        readBuffer->clear();
    }

    return 0;
}
