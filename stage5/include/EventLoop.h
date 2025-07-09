#pragma once
#include <functional>
#include <memory>
#include <mutex>
#include <vector>
#include <thread>
#include "common.h"

class Epoll;
class Channel;

class EventLoop
{
public:
    DISALLOW_COPY_AND_MOVE(EventLoop);
    EventLoop();
    ~EventLoop();

    void loop();
    void updateChannel(Channel*) const;
    void deleteChannel(Channel*) const;

    void doToDoList();  // 运行任务队列里的任务
    void queueOneFunc(std::function<void()> callback);  // 将任务添加到任务队列，当loop完成pooling后执行任务
    void runOneFunc(std::function<void()> callback);
    bool isInLoopThread();
    void handleRead();
private:
    std::unique_ptr<Epoll> ep;

    std::vector<std::function<void()>> to_do_list;
    std::mutex mutex_;
    int wakeup_fd;
    std::unique_ptr<Channel> wakeup_channel;
    bool calling_functors;
    pid_t tid;
};

