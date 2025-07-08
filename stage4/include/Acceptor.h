#pragma once
#include <functional>
#include <memory>
#include "common.h"

class EventLoop;
class Channel;

class Acceptor
{
public:
    DISALLOW_COPY_AND_MOVE(Acceptor);
    Acceptor(EventLoop *_loop, const char* ip, const int port);
    ~Acceptor();

    void create();
    void bind(const char* ip, const int port);
    void listen();

    void acceptConnection();
    void setNewConnectionCallback(std::function<void(int)> const &callback);
private:
    EventLoop *loop;
    int listenfd;
    std::unique_ptr<Channel> acceptChannel;
    std::function<void(int)> newConnectionCallback;
};

