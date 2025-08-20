#include "Acceptor.h"
#include "EventLoop.h"
#include "Channel.h"
#include <string.h>
#include <assert.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>

Acceptor::Acceptor(EventLoop *_loop, const char * ip, const int port) : loop(_loop), acceptChannel(nullptr), listenfd(-1){
    create();
    bind(ip, port);
    listen();
    acceptChannel = std::make_unique<Channel>(listenfd, loop);
    std::function<void()> cb = std::bind(&Acceptor::acceptConnection, this);
    acceptChannel->setReadCallback(cb);
    acceptChannel->enableRead();
}

Acceptor::~Acceptor(){
    loop->deleteChannel(acceptChannel.get());
    ::close(listenfd);
}

void Acceptor::acceptConnection(){
    struct sockaddr_in client_addr;
    socklen_t client_addrlength = sizeof(client_addr);
    assert(listenfd != -1);

    int client_fd = ::accept4(listenfd, (sockaddr*)&client_addr, &client_addrlength, SOCK_NONBLOCK | SOCK_CLOEXEC);
    
    if(client_fd == -1){
        std::cout << "Fail to accept" << std::endl;
    }   

    if(newConnectionCallback){
        newConnectionCallback(client_fd);
    }
}

void Acceptor::setNewConnectionCallback(std::function<void(int)> const &callback){
    newConnectionCallback = std::move(callback);
}

void Acceptor::create(){
    assert(listenfd == -1);
    listenfd = socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC,IPPROTO_TCP);

    // 端口快速复用和重启绑定
    int on=1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));

    if(listenfd == -1){
        std::cout << "Fail to creat lisen socket!" << std::endl;
    }
}

void Acceptor::bind(const char* ip, const int port){
    struct sockaddr_in addr;
    memset(&addr, 0 , sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);
    if(::bind(listenfd, (sockaddr*)&addr, sizeof(addr)) == -1){
        std::cout << "Fail to bind " << ip << ":" << port << std::endl;
    }
}

void Acceptor::listen(){
    assert(listenfd != -1);
    if(::listen(listenfd, SOMAXCONN) == -1){
        std::cout << "Fail to listen" << std::endl; 
    }
}

