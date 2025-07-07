#include <vector>
#include "EventLoop.h"
#include "Epoll.h"
#include "Channel.h"

EventLoop::EventLoop() : ep(nullptr){
    ep = std::make_unique<Epoll>();
}

EventLoop::~EventLoop(){

}

void EventLoop::loop() const{
    while(true){
        std::vector<Channel*> chs = ep->poll();
        for(auto it = chs.begin(); it != chs.end(); ++it){
            (*it)->handleEvent();
        }
    }
}

void EventLoop::updateChannel(Channel *ch) const{
    ep->updateChannel(ch);
}

void EventLoop::deleteChannel(Channel *ch) const{
    ep->deleteChannel(ch);
}
