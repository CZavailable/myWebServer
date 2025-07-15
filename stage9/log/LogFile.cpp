#include <iostream>
#include <string>
#include "LogFile.h"
#include "TimeStamp.h"

LogFile::LogFile(const char* filepath) : fp(::fopen(filepath, "a+")) , written_bytes(0) , lastflush(0) , lastwrite(0){
    if(!fp){
        std::string DefaultPath = std::move("../LogFiles/LogFile_" + TimeStamp::now().TimeStamp::toFormattedDefaultLogString() + ".log");
        fp = ::fopen(DefaultPath.data(), "a+");
    }
}

LogFile::~LogFile(){
    flush();
    if(!fp){
        fclose(fp);
    }
}

void LogFile::write(const char* data, int len){
    int pos = 0;
    while(pos != len){
        pos += static_cast<int>(fwrite_unlocked(data + pos, sizeof(char), len - pos, fp));
    }
    time_t now = ::time(nullptr);

    if(len != 0){
        lastwrite = now;
        written_bytes += len;
    }

    if(lastwrite - lastflush > FlushInterval){
        flush();
        lastflush = now;
    }
}

int64_t LogFile::writtenBytes() const{
    return written_bytes;
}

void LogFile::flush(){
    fflush(fp);
}

