#include "TcpConnection.h"
#include "Channel.h"
#include "Buffer.h"
#include "EventLoop.h"
#include <sys/socket.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <memory>


TcpConnection::TcpConnection(EventLoop *_loop, int _connfd, int _connid) : loop(_loop), connfd(_connfd), connid(_connid){
    if(loop != nullptr){
        channel = std::make_unique<Channel>(connfd, loop);
        channel->enableET();
        channel->setReadCallback(std::bind(&TcpConnection::handleMessage,this));
        channel->enableRead();
        state = ConnectionState::Connected;
    }
    read_Buffer = std::make_unique<Buffer>();
    send_Buffer = std::make_unique<Buffer>();
    // state = ConnectionState::Connected;
}

TcpConnection::~TcpConnection(){
    // ::close(connfd);    // 析构这里关闭了connfd文件描述符 
}

void TcpConnection::handleMessage(){
    read();
    if(onMessageCallback){
        onMessageCallback(this);
    }
}

void TcpConnection::handleClose(){
    // 这里也是处理连接关闭的情况，由TcpServer类定义
    if(state != ConnectionState::Disconnected){
        state = ConnectionState::Disconnected;
        if(deleteConnectionCallback){
            deleteConnectionCallback(connfd);
        }
    }
}

void TcpConnection::read(){
    assert(state == ConnectionState::Connected);
    read_Buffer->clear();
    readNonBlocking();
}

void TcpConnection::write(){
    assert(state == ConnectionState::Connected);
    writeNonBlocking();
    send_Buffer->clear();
}

void TcpConnection::readNonBlocking(){
    char buf[1024];
    while(true){
        memset(&buf, 0 , sizeof(buf));
        ssize_t bytes_read = ::read(connfd, buf, sizeof(buf));
        if(bytes_read > 0){
            read_Buffer->append(buf, bytes_read);
        }
        else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){
            printf("读取完毕!\n");
            break;
        }
        else if(bytes_read == -1 && errno == EINTR){
            printf("程序正常中断，继续读取!\n");
            continue;
        }
        else if(bytes_read == 0){
            printf("read EOF, client fd %d disconnected\n", connfd);
            handleClose();
            break;
        }
        else{
            printf("Other error on client fd %d\n", connfd);
            handleClose();
            break;
        }
    }
}

void TcpConnection::writeNonBlocking(){
    char buf[send_Buffer->size()];
    memcpy(buf, send_Buffer->c_str(), send_Buffer->size());
    int data_size = send_Buffer->size();
    int data_left = data_size;
    while(data_left > 0){
        ssize_t bytes_write = ::write(connfd, buf + data_size - data_left, data_left);
        if (bytes_write == -1 && errno == EINTR) {
            printf("continue writing\n");
            continue;
        }
        if (bytes_write == -1 && errno == EAGAIN) {
            break;
        }
        if (bytes_write == -1) {
            printf("Other error on client fd %d\n", connfd);
            handleClose();
            break;
        }
        data_left -= bytes_write;
    }
}

void TcpConnection::setSendBuf(const char* str){
    send_Buffer->setBuf(str);
}

Buffer* TcpConnection::read_buf(){
    return read_Buffer.get();
}

Buffer* TcpConnection::send_buf(){
    return send_Buffer.get();
}

void TcpConnection::send(const std::string& msg){
    setSendBuf(msg.c_str());
    write();
}

void TcpConnection::send(const char* msg){
    setSendBuf(msg);
    write();
}

void TcpConnection::deleteConnectionChannel(){
    loop->deleteChannel(channel.get());
}

void TcpConnection::setDeleteConnectionCallback(std::function<void(int)> const& callback){
    deleteConnectionCallback = std::move(callback);
}

void TcpConnection::setOnMessageCallback(std::function<void(TcpConnection*)> const& callback){
    onMessageCallback = std::move(callback);
}

EventLoop* TcpConnection::getLoop() const{
    return loop;
}

TcpConnection::ConnectionState TcpConnection::getState() const{
    return state;
}
int TcpConnection::getFd() const{
    return connfd;
}

int TcpConnection::getId() const{
    return connid;
}