#pragma once
#include <functional>
#include "common.h"
#include "TimeStamp.h"

class Timer{
public:
    DISALLOW_COPY_AND_MOVE(Timer);
    Timer(TimeStamp timestamp, std::function<void()> const& callback, double interval);

    void reStart(TimeStamp now);

    void run() const;

    TimeStamp getExpiration() const;

    bool getRepeat() const;
private:
    TimeStamp expiration;
    std::function<void()> callback;
    double interval;
    bool repeat;
};