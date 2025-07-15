#pragma once

#include <set>
#include <vector>
#include <memory>
#include <utility>
#include <functional>
#include <unistd.h>
#include <sys/timerfd.h>
#include "common.h"
#include "TimeStamp.h"

class Timer;
class EventLoop;
class Channel;

class TimerQueue{
public:
    DISALLOW_COPY_AND_MOVE(TimerQueue);
    TimerQueue(EventLoop* loop);
    ~TimerQueue();

    void creatTimerFd();

    void readTimerFd();
    void handleRead();

    void resetTimerFd(Timer* timer);
    void resetTimers();

    bool insert(Timer* timer);
    void addTimer(TimeStamp timestamp, std::function<void()> const& callback, double interval);
private:
    typedef std::pair<TimeStamp, Timer*> Entry;
    EventLoop* loop;
    int timerfd;
    std::unique_ptr<Channel> channel;

    std::set<Entry> timers;
    std::vector<Entry> active_timers;
};

