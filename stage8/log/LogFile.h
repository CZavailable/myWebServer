#pragma once

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "TimeStamp.h"

static const time_t FlushInterval = 3;

class LogFile{
public:
    LogFile(const char* filepath = nullptr);
    ~LogFile();

    void write(const char* data, int len);
    void flush();
    int64_t writtenBytes() const;
private:
    FILE* fp;
    int64_t written_bytes;
    time_t lastwrite;
    time_t lastflush;
};