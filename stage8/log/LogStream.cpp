#include <stdio.h>
#include "LogStream.h"

LogStream::LogStream(){}

LogStream::~LogStream(){}

void LogStream::append(const char* data, int len){
    buffer.append(data,len);
}

const LogStream::Buffer& LogStream::getBuffer() const{
    return buffer;
}

void LogStream::resetBuffer(){
    buffer.bzero();
}

LogStream& LogStream::operator<<(bool v){
    buffer.append(v ? "1" : "0", 1);
    return *this;
}

LogStream& LogStream::operator<<(short num){
    return (*this) << static_cast<int>(num);
}

LogStream& LogStream::operator<<(unsigned short num){
    return (*this) << static_cast<int>(num);
}

LogStream& LogStream::operator<<(int num){
    formatInteger(num);
    return *this;
}

LogStream& LogStream::operator<<(unsigned int num){
    formatInteger(num);
    return *this;
}

LogStream& LogStream::operator<<(long num){
    formatInteger(num);
    return *this;
}

LogStream& LogStream::operator<<(unsigned long num){
    formatInteger(num);
    return *this;
}

LogStream& LogStream::operator<<(long long num){
    formatInteger(num);
    return *this;
}

LogStream& LogStream::operator<<(unsigned long long num){
    formatInteger(num);
    return *this;
}

LogStream& LogStream::operator<<(const float& num){
    return (*this) << static_cast<const double>(num);
}

LogStream& LogStream::operator<<(const double& num){
    char buf[32];
    int len = snprintf(buf, sizeof(buf), "%g", num);
    buffer.append(buf, len);
    return *this;
}

LogStream& LogStream::operator<<(char v){
    buffer.append(&v, 1);
    return *this;
}

LogStream& LogStream::operator<<(const char* str){
    if(str){
        buffer.append(str, strlen(str));
    }
    else{
        buffer.append("(null)", 6);
    }
    return *this;
}

LogStream& LogStream::operator<<(const std::string& v){
    buffer.append(v.c_str(), v.size());
    return *this;
}