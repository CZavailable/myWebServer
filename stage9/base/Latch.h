#pragma once
#include <thread>
#include <condition_variable>
#include "common.h"

class Latch{
public:
    DISALLOW_COPY_AND_MOVE(Latch);
    explicit Latch(int count_) : count(count_){}

    void wait(){
        std::unique_lock<std::mutex> lock(mutex);
        while(count > 0){
            cv.wait(lock);
        }
    }

    void notify(){
        std::unique_lock<std::mutex> lock(mutex);
        --count;
        if(count == 0){
            cv.notify_all();
        }
    }
private:
    std::mutex mutex;
    std::condition_variable cv;
    int count;
};