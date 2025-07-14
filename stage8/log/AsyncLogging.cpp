#include <functional>
#include <chrono>
#include <vector>
#include <memory>
#include "LogFile.h"
#include "AsyncLogging.h"

AsyncLogging::AsyncLogging(const char* filepath_) : filepath(filepath_) , running(false) , latch(1){
    current = std::make_unique<Buffer>();
    next = std::make_unique<Buffer>();
}

AsyncLogging::~AsyncLogging(){
    if(running){
        stop();
    }
}

void AsyncLogging::start(){
    running = true;
    thread = std::thread(std::bind(&AsyncLogging::ThreadFunc, this));
    latch.wait();
}

void AsyncLogging::stop(){
    running = false;
    cv.notify_one();
    thread.join();
}

void AsyncLogging::flush(){
    fflush(stdout);
}

void AsyncLogging::append(const char* data, int len){
    std::unique_lock<std::mutex> lock(mutex);
    if(current->avail() >= len){
        current->append(data, len);
    }
    else{
        buffers.push_back(std::move(current));
        if(next){
            current = std::move(next);
        }
        else{
            current.reset(new Buffer());
        }
        current->append(data, len);
    }
    cv.notify_one();
}

void AsyncLogging::ThreadFunc(){
    latch.notify();

    std::unique_ptr<Buffer> new_current = std::make_unique<Buffer>();
    std::unique_ptr<Buffer> new_next = std::make_unique<Buffer>();
    std::unique_ptr<LogFile> logfile = std::make_unique<LogFile>();

    new_current->bzero();
    new_next->bzero();

    std::vector<std::unique_ptr<Buffer>> active_buffers;

    while(running){
        std::unique_lock<std::mutex> lock(mutex);
        if(buffers.empty()){
            cv.wait_until(lock, std::chrono::system_clock::now() + BufferWriteTimeout * std::chrono::milliseconds(1000) ,
                            []{return false;});
        }
        buffers.push_back(std::move(current));
        active_buffers.swap(buffers);
        current = std::move(new_current);
        if(!next){
            next = std::move(new_next);
        }

        for(const auto& buffer : active_buffers){
            logfile->write(buffer->getData(), buffer->len());
        }

        if(logfile->writtenBytes() >= FileMaximumSize){
            logfile.reset(new LogFile(filepath));
        }

        if(!new_current){
            new_current = std::move(active_buffers.back());
            active_buffers.pop_back();
            new_current->bzero();
        }

        if(!new_next){
            new_next = std::move(active_buffers.back());
            active_buffers.pop_back();
            new_next->bzero();
        }
        active_buffers.clear();
    }
}