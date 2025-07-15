#pragma once

#include <memory>
#include <thread>
#include <vector>
#include "common.h"

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool{
public:
    DISALLOW_COPY_AND_MOVE(EventLoopThreadPool);

    EventLoopThreadPool(EventLoop* loop);
    ~EventLoopThreadPool();

    void setThreadNums(int thread_nums);

    void start();

    EventLoop* nextLoop();
private:
    EventLoop* main_reactor_;
    std::vector<std::unique_ptr<EventLoopThread>> thread_;
    std::vector<EventLoop*> loops_;
    int thread_nums_;
    int next_;
};