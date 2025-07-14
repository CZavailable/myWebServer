#pragma once

#include <vector>
#include <memory>
#include <thread>
#include "Latch.h"
#include "Logging.h"

static const double BufferWriteTimeout = 3.0;
static const int64_t FileMaximumSize = 1024 * 1024 * 1024;

class AsyncLogging{
public:
    typedef FixedBuffer<FixedLargeBufferSize> Buffer;

    AsyncLogging(const char* filepath_ = nullptr);
    ~AsyncLogging();

    void stop();
    void start();

    void append(const char* data, int len);
    void flush();
    void ThreadFunc();

private:
    bool running;
    const char* filepath;
    std::mutex mutex;
    std::condition_variable cv;
    Latch latch;
    std::thread thread;
    std::unique_ptr<Buffer> current;
    std::unique_ptr<Buffer> next;
    std::vector<std::unique_ptr<Buffer>> buffers;
};