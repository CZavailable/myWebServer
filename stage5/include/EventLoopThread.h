#pragma once
#include <mutex>
#include <thread>
#include <condition_variable>
#include "common.h"

class EventLoop;

class EventLoopThread{
public:
    DISALLOW_COPY_AND_MOVE(EventLoopThread);
    EventLoopThread();
    ~EventLoopThread();

    EventLoop* startLoop();
private:
    void ThreadFunc();

    EventLoop* loop_;
    std::thread thread_;
    std::mutex mutex_;
    std::condition_variable cv_;
};