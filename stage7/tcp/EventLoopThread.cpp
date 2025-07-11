#include <mutex>
#include <thread>
#include <condition_variable>
#include "EventLoopThread.h"
#include "EventLoop.h"

EventLoopThread::EventLoopThread() : loop_(nullptr){}

EventLoopThread::~EventLoopThread(){}

EventLoop* EventLoopThread::startLoop(){
    thread_ = std::thread(std::bind(&EventLoopThread::ThreadFunc, this));
    EventLoop* loop = nullptr;

    {
        std::unique_lock<std::mutex> lock(mutex_);
        while(loop_ == nullptr){
            cv_.wait(lock);
        }
        loop = loop_;
    }

    return loop;
}

void EventLoopThread::ThreadFunc(){
    EventLoop loop;

    {
        std::unique_lock<std::mutex> lock(mutex_);
        loop_ = &loop;
        cv_.notify_one();
    }

    loop_->loop();

    {
        std::unique_lock<std::mutex> lock(mutex_);
        loop_ = nullptr;
    }
}