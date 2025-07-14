#pragma once
#include <functional>
#include <memory>
#include "common.h"

class EventLoop;

class Channel
{
public:
    DISALLOW_COPY_AND_MOVE(Channel);
    Channel(int _fd, EventLoop *_loop);
    ~Channel();

    void handleEvent() const;
    void handleEventGuard() const;
    void enableRead();
    void enableWrite();
    void enableET();
    void disableWrite();

    int getFd() const;
    short getListenEvent() const;
    short getReadyEvent() const;
    bool isInEpoll() const;
    void setInEpoll(bool _in = true);

    void setReadyEvent(int ev);
    void setReadCallback(std::function<void()> const& callback);
    void setWriteCallback(std::function<void()> const& callback);

    void Tie(const std::shared_ptr<void>& ptr);
private:
    EventLoop *loop;
    int fd;
    short listen_event;
    short ready_event;
    bool inEpoll;
    std::function<void()> readCallback;
    std::function<void()> writeCallback;

    bool tied;
    std::weak_ptr<void> tie;
};

