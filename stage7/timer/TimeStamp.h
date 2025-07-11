#pragma once 
#include <string>
#include <stdio.h>
#include <sys/time.h>

const int kMicrosecond2Second = 1000 * 1000;

class TimeStamp{
public:
    TimeStamp() : micro_seconds(0){}
    TimeStamp(int64_t micro_seconds) : micro_seconds(micro_seconds){}
    
    bool operator<(const TimeStamp& rhs) const{
        return micro_seconds < rhs.getMicroseconds();
    }

    bool operator==(const TimeStamp& rhs) const{
        return micro_seconds == rhs.getMicroseconds();
    }

    int64_t getMicroseconds() const{
        return micro_seconds;
    }

    std::string toFormattedString() const{
        char buf[64] = {0};
        time_t seconds = static_cast<time_t>(micro_seconds / kMicrosecond2Second);
        struct tm tm_time;
        localtime_r(&seconds, &tm_time);
        int micro_seconds_ = static_cast<int>(micro_seconds % kMicrosecond2Second);
        snprintf(buf, sizeof(buf), "%4d-%02d-%02d %02d:%02d:%02d.%06d",
                tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec, micro_seconds_);
        return buf;
    }

    static TimeStamp now();
    static TimeStamp addTime(TimeStamp timestamp, double add_seconds);
private:
    int64_t micro_seconds;
};

inline TimeStamp TimeStamp::now(){
    struct timeval time;
    gettimeofday(&time, NULL);
    return TimeStamp(time.tv_sec * kMicrosecond2Second + time.tv_usec);
}

inline TimeStamp TimeStamp::addTime(TimeStamp timestamp, double add_seconds){
    int64_t add_microseconds = static_cast<int64_t>(add_seconds) * kMicrosecond2Second;   
    return TimeStamp(timestamp.getMicroseconds() + add_microseconds);
}