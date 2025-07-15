#include <sys/socket.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <memory>
#include "TcpConnection.h"
#include "Channel.h"
#include "Buffer.h"
#include "EventLoop.h"
#include "HttpContext.h"
#include "TimeStamp.h"
#include "Logging.h"


TcpConnection::TcpConnection(EventLoop *_loop, int _connfd, int _connid) : loop(_loop), connfd(_connfd), connid(_connid){
    if(loop != nullptr){
        channel = std::make_unique<Channel>(connfd, loop);
        channel->enableET();
        channel->setReadCallback(std::bind(&TcpConnection::handleMessage,this));
        channel->setWriteCallback(std::bind(&TcpConnection::handleWrite,this));
        // channel->enableRead();
        state = ConnectionState::Connected;
    }
    read_Buffer = std::make_unique<Buffer>();
    send_Buffer = std::make_unique<Buffer>();
    context = std::make_unique<HttpContext>();
    // state = ConnectionState::Connected;
}

TcpConnection::~TcpConnection(){
    ::close(connfd);    // 析构这里关闭了connfd文件描述符 
}

void TcpConnection::handleMessage(){
    read();
    if(onMessageCallback){
        onMessageCallback(shared_from_this());
    }
}

void TcpConnection::handleWrite(){
    LOG_INFO << "TcpConnection::handleWrite";
    write();
}

void TcpConnection::handleClose(){
    // 这里也是处理连接关闭的情况，由TcpServer类定义
    if(state != ConnectionState::Disconnected){
        state = ConnectionState::Disconnected;
        loop->deleteChannel(channel.get());
        if(deleteConnectionCallback){
            deleteConnectionCallback(shared_from_this());
        }
    }
}

void TcpConnection::read(){
    assert(state == ConnectionState::Connected);
    readNonBlocking();
}

void TcpConnection::write(){
    assert(state == ConnectionState::Connected);
    writeNonBlocking();
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
    int remaining = send_Buffer->readableBytes();
    int send_size = static_cast<int>(::write(connfd, send_Buffer->peek(), remaining));
    if(send_size == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)){
        send_size = 0;
    }
    else if(send_size == -1){
        LOG_ERROR << "TcpConnection::send - TcpConnection send ERROR";
    }
    remaining -= send_size;
    send_Buffer->retrieve(send_size);
}

Buffer* TcpConnection::read_buf(){
    return read_Buffer.get();
}

Buffer* TcpConnection::send_buf(){
    return send_Buffer.get();
}

void TcpConnection::send(const char* msg, int len){
    int remaining = len;
    int send_size = 0;

    if(send_Buffer->readableBytes() == 0){
        send_size = static_cast<int>(::write(connfd, msg, len));

        if(send_size >= 0){
            remaining -= send_size;
        }
        else if(send_size == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)){
            send_size = 0;
        }
        else{
            LOG_ERROR << "TcpConnection::send - TcpConnection send ERROR";
            return;
        }
    }
    assert(remaining <= len);
    if(remaining > 0){
        send_Buffer->append(msg + send_size, remaining);
        channel->enableWrite();
    }
    // send_Buffer->append(msg, len);
    // write();
}

void TcpConnection::send(const std::string& msg){
    send(msg.data(), static_cast<int>(msg.size()));
}

void TcpConnection::send(const char* msg){
    send(msg, static_cast<int>(strlen(msg)));
}

void TcpConnection::connectionEstablished(){
    state = ConnectionState::Connected;
    channel->Tie(shared_from_this());
    channel->enableRead();
    if(onConnectionCallback){
        onConnectionCallback(shared_from_this());
    }
}

void TcpConnection::connectionDestructor(){
    // loop->deleteChannel(channel.get());
}

void TcpConnection::updateTimeStamp(TimeStamp now){
    timestamp = now;
}

void TcpConnection::setDeleteConnectionCallback(std::function<void(const std::shared_ptr<TcpConnection>&)> const& callback){
    deleteConnectionCallback = std::move(callback);
}

void TcpConnection::setOnMessageCallback(std::function<void(const std::shared_ptr<TcpConnection>&)> const& callback){
    onMessageCallback = std::move(callback);
}

void TcpConnection::setOnConnectionCallback(std::function<void(const std::shared_ptr<TcpConnection>&)> const& callback){
    onConnectionCallback = std::move(callback);
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

HttpContext* TcpConnection::getContext() const{
    return context.get();
}

TimeStamp TcpConnection::getTimeStamp() const{
    return timestamp;
}