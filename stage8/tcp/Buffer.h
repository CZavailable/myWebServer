#pragma once
#include <string>
#include "common.h"

class Buffer
{
public:
    DISALLOW_COPY_AND_MOVE(Buffer);
    Buffer() = default;
    ~Buffer() = default;
    
    void append(const char* _str, int _size);
    ssize_t size() const;
    const char* c_str() const;
    void clear();
    
    const std::string& getBuf() const;
    void setBuf(const char*);
private:
    std::string buf;
};

