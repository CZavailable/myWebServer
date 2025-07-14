#include <string>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <assert.h>
#include "common.h"

static const int FixedBufferSize = 4096;
static const int FixedLargeBufferSize = 4096 * 1000;
static const int kMaxNumericSize = 48;

template <int SIZE>
class FixedBuffer{
public:
    FixedBuffer();
    ~FixedBuffer();

    void append(const char* buf, int len);
    const char* getData() const;
    int len() const;
    char* getCur();
    int avail() const;
    void add(int len);
    void reset();
    const char* end() const;
    void bzero();
private:
    char data[SIZE];
    char* cur;
};

class LogStream{
public:
    LogStream();
    ~LogStream();

    DISALLOW_COPY_AND_MOVE(LogStream);
    typedef LogStream self;
    typedef FixedBuffer<FixedBufferSize> Buffer;
    
    void append(const char* data, int len);
    const Buffer& getBuffer() const;
    void resetBuffer();

    self& operator<<(bool v);
    self& operator<<(short num);
    self& operator<<(unsigned short num);
    self& operator<<(int num);
    self& operator<<(unsigned int num);
    self& operator<<(long num);
    self& operator<<(unsigned long num);
    self& operator<<(long long num);
    self& operator<<(unsigned long long num);
    self& operator<<(const float& num);
    self& operator<<(const double& num);
    self& operator<<(char v);
    self& operator<<(const char* str);
    self& operator<<(const std::string& v);
private:
    template <typename T>
    void formatInteger(T value);
    Buffer buffer;
};

template <typename T>
void LogStream::formatInteger(T value){
    if(buffer.avail() >= kMaxNumericSize){
        char* buf = buffer.getCur();
        char* now = buf;
        do{
            int remainder = value % 10;
            *(now++) = remainder + '0';
            value /= 10;
        }while(value != 0);
        if(value < 0){
            *(now++) = '-';
        }
        std::reverse(buf, now);
        buffer.add(now - buf);
    }
}

class Fmt{
public:
    template <typename T>
    Fmt(const char* fmt, T val);
    const char* getData() const{
        return buf;
    }
    int len() const{
        return length;
    }
private:
    char buf[32];
    int length;
};

template <typename T>
Fmt::Fmt(const char* fmt, T val){
    static_assert(std::is_arithmetic<T>::value == true, "Must be arithmetic type");

    length = snprintf(buf, sizeof(buf), fmt, val);
    assert(static_cast<size_t>(length) < sizeof(buf));
}

inline LogStream& operator<<(LogStream& s, const Fmt& fmt){
    s.append(fmt.getData(), fmt.len());
    return s;
}

template Fmt::Fmt(const char* fmt, char);
template Fmt::Fmt(const char* fmt, short);
template Fmt::Fmt(const char* fmt, unsigned short);
template Fmt::Fmt(const char* fmt, int);
template Fmt::Fmt(const char* fmt, unsigned int);
template Fmt::Fmt(const char* fmt, long);
template Fmt::Fmt(const char* fmt, unsigned long);
template Fmt::Fmt(const char* fmt, long long);
template Fmt::Fmt(const char* fmt, unsigned long long);
template Fmt::Fmt(const char* fmt, float);

// FixedBuffer的定义，不支持分离编译
template <int SIZE>
FixedBuffer<SIZE>::FixedBuffer() : cur(data){}

template <int SIZE>
FixedBuffer<SIZE>::~FixedBuffer(){}

template <int SIZE>
void FixedBuffer<SIZE>::append(const char* buf, int len){
    if(avail() > len){
        memcpy(cur, buf, len);
        cur += len;
    }
}

template <int SIZE>
const char* FixedBuffer<SIZE>::getData() const{
    return data;
}

template <int SIZE>
int FixedBuffer<SIZE>::len() const{
    return static_cast<int>(cur - data);
}

template <int SIZE>
char* FixedBuffer<SIZE>::getCur(){
    return cur;
}

template <int SIZE>
int FixedBuffer<SIZE>::avail() const{
    return static_cast<int>(end() - cur);
}

template <int SIZE>
void FixedBuffer<SIZE>::add(int len){
    cur += len;
}

template <int SIZE>
void FixedBuffer<SIZE>::reset(){
    cur = data;
}

template <int SIZE>
const char* FixedBuffer<SIZE>::end() const{
    return data + sizeof(data);
}

template <int SIZE>
void FixedBuffer<SIZE>::bzero(){
    memset(data, '\0', sizeof(data));
    cur = data;
}