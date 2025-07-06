#include "Connection.h"
#include "Socket.h"
#include "Channel.h"
#include "util.h"
#include "Buffer.h"
#include <unistd.h>
#include <string.h>
#include <utility>
#include <iostream>
#include <assert.h>

Connection::Connection(EventLoop *_loop, Socket *_sock) : loop(_loop), sock(_sock), channel(nullptr), read_Buffer(nullptr){
    if(loop != nullptr){
        channel = new Channel(loop, sock->getFd());
        channel->enableRead();
        channel->useET();
    }
    // std::function<void()> cb = std::bind(&Connection::echo, this, sock->getFd());
    // channel->setReadCallback(cb);
    read_Buffer = new Buffer();
    send_Buffer = new Buffer();
    state = State::Connected;
}

Connection::~Connection(){
    if(loop != nullptr){
        delete channel;
    }
    delete sock;
    delete read_Buffer;
    delete send_Buffer;
}

void Connection::read(){
    assert(state == State::Connected);
    read_Buffer->clear();
    readNonBlocking();
}

void Connection::write(){
    assert(state == State::Connected);
    writeNonBlocking();
    send_Buffer->clear();
}

void Connection::readNonBlocking(){
    int sockfd = sock->getFd();
    char buf[1024];
    while(true){
        memset(&buf, 0 , sizeof(buf));
        ssize_t bytes_read = ::read(sockfd, buf, sizeof(buf));
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
            printf("read EOF, client fd %d disconnected\n", sockfd);
            state = State::Closed;
            break;
        }
        else{
            printf("Other error on client fd %d\n", sockfd);
            state = State::Closed;
            break;
        }

    }
}

void Connection::writeNonBlocking(){
    int sockfd = sock->getFd();
    char buf[send_Buffer->size()];
    memcpy(buf, send_Buffer->c_str(), send_Buffer->size());
    int data_size = send_Buffer->size();
    int data_left = data_size;
    while(data_left > 0){
        ssize_t bytes_write = ::write(sockfd, buf + data_size - data_left, data_left);
        if (bytes_write == -1 && errno == EINTR) {
            printf("continue writing\n");
            continue;
        }
        if (bytes_write == -1 && errno == EAGAIN) {
            break;
        }
        if (bytes_write == -1) {
            printf("Other error on client fd %d\n", sockfd);
            state = State::Closed;
            break;
        }
        data_left -= bytes_write;
    }
}

void Connection::close(){
    deleteConnectionCallback(sock);
}

Connection::State Connection::getState(){
    return state;
}

void Connection::setSendBuffer(const char* str){
    send_Buffer->setBuf(str);
}

Buffer* Connection::getSendBuffer(){
    return send_Buffer;
}

const char* Connection::sendBuffer(){
    return send_Buffer->c_str();
}

void Connection::getLineSendBuffer(){
    send_Buffer->getline();
}

Buffer* Connection::getReadBuffer(){
    return read_Buffer;
}

const char* Connection::readBuffer(){
    return read_Buffer->c_str();
}

void Connection::setDeleteConnectionCallback(std::function<void(Socket*)> const& callback){
    deleteConnectionCallback = callback;
}

void Connection::setOnConnectionCallback(std::function<void(Connection*)> const& callback){
    onConnectionCallback = callback;
    channel->setReadCallback([this](){
        onConnectionCallback(this);
    });
}

Socket* Connection::getSocket(){
    return sock;
}