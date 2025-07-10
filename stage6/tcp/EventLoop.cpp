#include <vector>
#include <memory>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <sys/eventfd.h>
#include <assert.h>
#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"
#include "CurrentThread.h"

EventLoop::EventLoop() : ep(nullptr){
    ep = std::make_unique<Epoll>();
    wakeup_fd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    wakeup_channel = std::make_unique<Channel>(wakeup_fd, this);
    calling_functors = false;

    wakeup_channel->setReadCallback(std::bind(&EventLoop::handleRead,this));
    wakeup_channel->enableRead();
}

EventLoop::~EventLoop(){
    deleteChannel(wakeup_channel.get());
    ::close(wakeup_fd);
}

void EventLoop::loop() {
    tid = CurrentThread::tid();
    while(true){
        std::vector<Channel*> chs = ep->poll();
        for(auto it = chs.begin(); it != chs.end(); ++it){
            (*it)->handleEvent();
        }
        doToDoList();
    }
}

void EventLoop::updateChannel(Channel *ch) const{
    ep->updateChannel(ch);
}

void EventLoop::deleteChannel(Channel *ch) const{
    ep->deleteChannel(ch);
}

void EventLoop::doToDoList(){
    calling_functors = true;
    std::vector<std::function<void()>> functors;

    {
        std::unique_lock<std::mutex> lock(mutex_);
        functors.swap(to_do_list);
    }

    for(const auto& func : functors){
        func();
    }
}

void EventLoop::queueOneFunc(std::function<void()> callback){
    {
        std::unique_lock<std::mutex> lock(mutex_);
        to_do_list.emplace_back(std::move(callback));
    }
    if(!isInLoopThread() || calling_functors){
        uint64_t write_one_byte = 1;
        ssize_t write_size = ::write(wakeup_fd, &write_one_byte, sizeof(write_one_byte));
        (void) write_size;
        assert(write_size == sizeof(write_one_byte));
    }
}

void EventLoop::runOneFunc(std::function<void()> callback){
    if(isInLoopThread()){
        callback();
    }else{
        queueOneFunc(callback);
    }
}

bool EventLoop::isInLoopThread(){
    return CurrentThread::tid() == tid;
}

void EventLoop::handleRead(){
    uint64_t read_one_byte = 1;
    ssize_t read_size = ::read(wakeup_fd, &read_one_byte, sizeof(read_one_byte));
    (void) read_size;
    assert(read_size == sizeof(read_one_byte));
}
