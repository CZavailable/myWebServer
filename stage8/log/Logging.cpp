#include <utility>
#include "CurrentThread.h"
#include "Logging.h"

__thread char t_time[64];
__thread time_t t_lastsecond;

struct Template{
    Template(const char* str_, unsigned len_) : str(str_), len(len_){}
    const char* str;
    const unsigned len;
};

inline LogStream& operator<<(LogStream& s, Template v){
    s.append(v.str, v.len);
    return s;
}

inline LogStream& operator<<(LogStream& s, const Logger::SourceFile v){
    s.append(v.data, v.size);
    return s;
}

Logger::SourceFile::SourceFile(const char* data_) : data(data_), size(static_cast<int>(strlen(data_))){
    const char* forward_slash = strrchr(data, '/');
    if(forward_slash){
        data = forward_slash + 1;
        size -= static_cast<int>(data - data_);
    }
}

Logger::Impl::Impl(Logger::LogLevel level_, const Logger::SourceFile& source_, int line_) : level(level_) , sourcefile(source_) , line(line_){
    formattedTime();
    CurrentThread::tid();

    stream << Template(CurrentThread::tidString(), CurrentThread::tidStringLength());
    stream << Template(getLogLevel(), 6);
}

void Logger::Impl::formattedTime(){
    TimeStamp now = TimeStamp::now();
    time_t seconds = static_cast<time_t>(now.getMicroseconds() / kMicrosecond2Second);
    int microseconds = static_cast<int>(now.getMicroseconds() % kMicrosecond2Second);

    if(t_lastsecond != seconds){
        struct tm tm_time;
        localtime_r(&seconds, &tm_time);
        snprintf(t_time, sizeof(t_time), "%4d%02d%02d %02d:%02d:%02d.",
                tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
        t_lastsecond = seconds;
    }

    Fmt us(".%06dZ  ", microseconds);
    stream << Template(t_time, 17) << Template(us.getData(), 9);
}

void Logger::Impl::finish(){
    stream << " - " << sourcefile.data << ":" << line << "\n";
}

LogStream& Logger::Impl::getStream(){
    return stream;
}

const char* Logger::Impl::getLogLevel() const{
    switch(level){
        case DEBUG:
            return "DEBUG  ";
        case INFO:
            return "INFO  ";
        case WARN:
            return "WARN  ";
        case ERROR:
            return "ERROR ";
        case FATAL:
            return "FATAL ";
    }
    return nullptr;
}

void defaultOutput(const char* msg, int len){
    fwrite(msg, 1, len, stdout);
}

void defaultFlush(){
    fflush(stdout);
}

Logger::outputFunc g_output = defaultOutput;
Logger::flushFunc g_flush = defaultFlush;
Logger::LogLevel g_logLevel = Logger::LogLevel::INFO;

Logger::Logger(const char* file_, int line_, Logger::LogLevel level_) : impl(level_,file_,line_){}


Logger::~Logger(){
    impl.finish();
    const LogStream::Buffer& buf(getStream().getBuffer());
    g_output(buf.getData(),buf.len());

    if(impl.level == FATAL){
        g_flush();
        abort();
    }
}

LogStream& Logger::getStream(){
    return impl.getStream();
}

void Logger::setOutput(Logger::outputFunc func){
    g_output = func;
}

void Logger::setFlush(Logger::flushFunc func){
    g_flush = func;
}

void Logger::setLogLevel(Logger::LogLevel level){
    g_logLevel = level;
}