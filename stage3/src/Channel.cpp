#include "Channel.h"
#include "EventLoop.h"

#include <utility>
#include <unistd.h>
#include <sys/epoll.h>
#include <stdio.h>

Channel::Channel(int _fd, EventLoop *_loop) 
    : loop(_loop), fd(_fd), listen_event(0), ready_event(0), inEpoll(false){}

Channel::~Channel(){
    if(fd != -1){
        close(fd);
        fd = -1;
    }
}

void Channel::handleEvent() const{
    if(ready_event & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)){
        if(readCallback){
            readCallback();
        }
    }
    if(ready_event & EPOLLOUT){
        if(writeCallback){
            writeCallback();
        }
    }
}

void Channel::enableRead(){
    listen_event |= (EPOLLIN | EPOLLPRI);
    loop->updateChannel(this);
}

void Channel::enableWrite(){
    listen_event |= EPOLLOUT;
    loop->updateChannel(this);
}

void Channel::enableET(){
    listen_event |= EPOLLET;
    loop->updateChannel(this);
}

int Channel::getFd() const{
    return fd;
}

short Channel::getListenEvent() const{
    return listen_event;
}

short Channel::getReadyEvent() const{
    return ready_event;
}

bool Channel::isInEpoll() const{
    return inEpoll;
}

void Channel::setInEpoll(bool _in){
    inEpoll = _in;
}

void Channel::setReadyEvent(int _ev){
    ready_event = _ev;
}

void Channel::setReadCallback(std::function<void()> const& callback){
    readCallback = std::move(callback);
}

void Channel::setWriteCallback(std::function<void()> const& callback){
    writeCallback = std::move(callback);
}