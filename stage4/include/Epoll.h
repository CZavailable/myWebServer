#pragma once
#include <sys/epoll.h>
#include <vector>
#include "common.h"

class Channel;
class Epoll
{
public:
    DISALLOW_COPY_AND_MOVE(Epoll);
    Epoll();
    ~Epoll();

    void updateChannel(Channel*) const;
    void deleteChannel(Channel*) const;

    std::vector<Channel*> poll(int timeout = -1) const;
private:
    int epfd;
    struct epoll_event* events;
};

