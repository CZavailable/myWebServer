#pragma once

#include <string.h>
#include "common.h"
#include "TimeStamp.h"
#include "LogStream.h"

class Logger{
public:
    DISALLOW_COPY_AND_MOVE(Logger);
    enum LogLevel{
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    class SourceFile{
    public:
        SourceFile(const char* data_);
        const char* data;
        int size;
    };

    Logger(const char* file, int line, LogLevel level);
    ~Logger();

    LogStream& getStream();

    static LogLevel getLogLevel();
    static void setLogLevel(LogLevel level);

    typedef void (*outputFunc)(const char* data, int len);
    typedef void (*flushFunc)();

    static void setOutput(outputFunc);
    static void setFlush(flushFunc);
private:
    class Impl{
    public:
        DISALLOW_COPY_AND_MOVE(Impl);
        Impl(Logger::LogLevel level_, const SourceFile& source_, int line_); 
        void formattedTime();
        void finish();

        LogStream& getStream();
        const char* getLogLevel() const;
        Logger::LogLevel level;

    private:
        Logger::SourceFile sourcefile;
        int line;
        LogStream stream;
    };
    Impl impl;
};

extern Logger::LogLevel g_logLevel;
inline Logger::LogLevel Logger::getLogLevel(){
    return g_logLevel;
}

#define LOG_DEBUG if(Logger::getLogLevel() <= Logger::DEBUG)  \
    Logger(__FILE__,__LINE__,Logger::DEBUG,__func__).getStream()
#define LOG_INFO if(Logger::getLogLevel() <= Logger::INFO)  \
    Logger(__FILE__,__LINE__,Logger::INFO).getStream()
#define LOG_WARN Logger(__FILE__,__LINE__,Logger::WARN).getStream()
#define LOG_ERROR Logger(__FILE__,__LINE__,Logger::ERROR).getStream()
#define LOG_FATAL Logger(__FILE__,__LINE__,Logger::FATAL).getStream()
