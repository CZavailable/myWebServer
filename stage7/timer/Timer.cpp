#include <functional>
#include "Timer.h"
#include "TimeStamp.h"

Timer::Timer(TimeStamp timestamp, std::function<void()> const& callback, double interval = 0.0)
            : expiration(timestamp), callback(std::move(callback)), interval(interval), repeat(interval > 0.0){}

void Timer::reStart(TimeStamp now){
    expiration = TimeStamp::addTime(now, interval);
}

void Timer::run() const{
    callback();
}

TimeStamp Timer::getExpiration() const{
    return expiration;
}

bool Timer::getRepeat() const{
    return repeat;
}