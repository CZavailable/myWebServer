#include "Socket.h"
#include "InetAddress.h"
#include "util.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>

Socket::Socket() : fd(-1){
    fd = socket(AF_INET, SOCK_STREAM, 0);
    errif(fd == -1, "socket create error");
}
Socket::Socket(int _fd) : fd(_fd){
    errif(fd == -1, "socket create error");
}

Socket::~Socket(){
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}

void Socket::bind(InetAddress *_addr){
    struct sockaddr_in addr = _addr->getAddr();
    errif(::bind(fd, (sockaddr*)&addr, sizeof(addr)) == -1, "socket bind error");
}

void Socket::listen(){
    errif(::listen(fd, SOMAXCONN) == -1, "socket listen error");
}

void Socket::setnonblocking(){
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int Socket::accept(InetAddress *_addr){
    int clnt_sockfd = -1;
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    socklen_t addr_len = sizeof(addr);
    if(fcntl(fd, F_GETFL) & O_NONBLOCK){
        // 当前socket是非阻塞socket
        while(true){
            clnt_sockfd = ::accept(fd, (sockaddr*)&addr, &addr_len);
            // 还没有客户端连接
            if(clnt_sockfd == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){
                // printf("no connection yet\n");
                continue;
            } else if(clnt_sockfd == -1){
                errif(true, "socket accept error");
            } else{
                break;
            }
        }
    }else{
        // 当前socket是阻塞socket
        clnt_sockfd = ::accept(fd, (sockaddr*)&addr, &addr_len);
        errif(clnt_sockfd == -1, "socket accept error");
    }
    _addr->setInetAddr(addr);
    return clnt_sockfd;
}

void Socket::connect(InetAddress *_addr){
    struct sockaddr_in addr = _addr->getAddr();
    // 当前socket是非阻塞socket
    if(fcntl(fd, F_GETFL) & O_NONBLOCK){
        while(true){
            int ret = ::connect(fd, (sockaddr*)&addr, sizeof(addr));
            if(ret == 0){
                break;
            }
            else if(ret == -1 && (errno == EINPROGRESS)){
                continue;
            }
            else if(ret == -1){
                errif(true, "socket connect error");
            }
        }
    }
    else {
        errif(::connect(fd, (sockaddr*)&addr, sizeof(addr)) == -1, "socket connect error");
    }
}

int Socket::getFd(){
    return fd;
}