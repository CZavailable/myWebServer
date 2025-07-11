#include "Epoll.h"
#include "Channel.h"
#include <unistd.h>
#include <string.h>

#define MAX_EVENTS 1000

Epoll::Epoll() : epfd(-1), events(nullptr){
    epfd = epoll_create1(0);
    events = new epoll_event[MAX_EVENTS];
    memset(events, 0, sizeof(*events) * MAX_EVENTS);
}

Epoll::~Epoll(){
    if(epfd != -1){
        ::close(epfd);
    }
    delete [] events;
}

std::vector<Channel*> Epoll::poll(int timeout) const{
    std::vector<Channel*> activeChannels;
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, timeout);
    if(nfds == -1){
        perror("epoll wait error");
    }
    for(int i = 0; i < nfds; ++i){
        Channel *ch = (Channel*)events[i].data.ptr;
        int revents = events[i].events;
        ch->setReadyEvent(revents);
        activeChannels.emplace_back(ch);
    }
    return activeChannels;
}

void Epoll::updateChannel(Channel *channel) const{
    int fd = channel->getFd();
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.ptr = channel;
    ev.events = channel->getListenEvent();
    if(!channel->isInEpoll()){
        if(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1){
            perror("epoll add error");
        }
        channel->setInEpoll(true);
    } else{
        if(epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1){
            perror("epoll modify error");
        }
    }
}

void Epoll::deleteChannel(Channel *channel) const{
    int fd = channel->getFd();
    if(epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL) == -1){
        perror("epoll delete error");
    }
    channel->setInEpoll(false);
}