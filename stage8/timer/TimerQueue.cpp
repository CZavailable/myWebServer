#include <iostream>
#include <cstring>
#include <assert.h>
#include <sys/timerfd.h>
#include "EventLoop.h"
#include "Channel.h"
#include "Timer.h"
#include "TimeStamp.h"
#include "TimerQueue.h"

TimerQueue::TimerQueue(EventLoop* loop) : loop(loop){
    creatTimerFd();
    channel = std::make_unique<Channel>(timerfd, loop);
    channel->setReadCallback(std::bind(&TimerQueue::handleRead, this));
    channel->enableRead();
}

TimerQueue::~TimerQueue(){
    loop->deleteChannel(channel.get());
    close(timerfd);
    for(const auto& entry : timers){
        delete entry.second;
    }
}

void TimerQueue::creatTimerFd(){
    timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    if(timerfd < 0){
        printf("TimerQueue::creatTimerFd error");
    }
}

void TimerQueue::readTimerFd(){
    uint64_t read_byte;
    ssize_t readn = ::read(timerfd, &read_byte, sizeof(read_byte));
    if(readn != sizeof(read_byte)){
        printf("TimerQueue::readTimerFd read error");
    }
}

void TimerQueue::handleRead(){
    readTimerFd();
    active_timers.clear();

    auto end = timers.lower_bound(Entry(TimeStamp::now(), reinterpret_cast<Timer*>(UINTPTR_MAX)));
    active_timers.insert(active_timers.end(), timers.begin(), end);

    timers.erase(timers.begin(), end);
    for(const auto& entry : active_timers){
        entry.second->run();
    }
    resetTimers();
}

void TimerQueue::addTimer(TimeStamp timestamp, std::function<void()> const& callback, double interval){
    Timer* timer = new Timer(timestamp, callback, interval);
    if(insert(timer)){
        resetTimerFd(timer);
    }
}

bool TimerQueue::insert(Timer* timer){
    bool reset_instantly = false;
    if(timers.empty() || timer->getExpiration() < timers.begin()->first){
        reset_instantly = true;
    }
    timers.emplace(std::move(Entry(timer->getExpiration(), timer)));
    return reset_instantly;
}

void TimerQueue::resetTimers(){
    for(auto& entry : active_timers){
        if((entry.second)->getRepeat()){
            auto timer = entry.second;
            timer->reStart(TimeStamp::now());
            insert(timer);
        }
        else{
            delete entry.second;
        }
    }

    if(!timers.empty()){
        resetTimerFd(timers.begin()->second);
    }
}

void TimerQueue::resetTimerFd(Timer* timer){
    struct itimerspec new_;
    struct itimerspec old_;
    memset(&new_, '\0', sizeof(new_));
    memset(&old_, '\0', sizeof(old_));
    
    int64_t micro_seconds_dif = timer->getExpiration().getMicroseconds() - TimeStamp::now().getMicroseconds();
    if(micro_seconds_dif < 100){
        micro_seconds_dif = 100;
    }

    new_.it_value.tv_sec = static_cast<time_t>(
        micro_seconds_dif / kMicrosecond2Second);
    new_.it_value.tv_nsec = static_cast<long>((
        micro_seconds_dif % kMicrosecond2Second) * 1000);
    int ret = ::timerfd_settime(timerfd, 0, &new_, &old_);
    
    assert(ret != -1);
    (void)ret;
}