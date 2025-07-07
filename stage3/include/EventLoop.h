#pragma once
#include <functional>
#include <memory>
#include "common.h"

class Epoll;
class Channel;

class EventLoop
{
public:
    DISALLOW_COPY_AND_MOVE(EventLoop);
    EventLoop();
    ~EventLoop();

    void loop() const;
    void updateChannel(Channel*) const;
    void deleteChannel(Channel*) const;
private:
    std::unique_ptr<Epoll> ep;
};

