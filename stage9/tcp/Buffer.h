#pragma once

#include <vector>
#include <memory>
#include <string>
#include <cstring>
#include "common.h"

static const int kPrePendIndex = 8;
static const int kInitalSize = 1024;

class Buffer
{
public:
    DISALLOW_COPY_AND_MOVE(Buffer);
    Buffer();
    ~Buffer();
    
    char* begin();
    const char* begin() const;

    char* beginRead();
    const char* beginRead() const;

    char* beginWrite();
    const char* beginWrite() const;

    int readableBytes() const;
    int writableBytes() const;
    int prependaBlebytes() const;

    void append(const char* message);
    void append(const char* message, int len);
    void append(const std::string& message);

    char* peek();
    const char* peek() const;
    std::string peekAsString(int len);
    std::string peekAllAsString();

    void retrieve(int len);
    std::string retrieveAsString(int len);

    void retrieveAll();
    std::string retrieveAllAsString();

    void retrieveUtil(const char* end);
    std::string retrieveUtilAsString(const char* end);

    void ensureWritableBytes(int len);

    // ssize_t size() const;
    // const char* c_str() const;
    // void clear();
    
    // const std::string& getBuf() const;
    // void setBuf(const char*);
private:
    std::vector<char> buffer;
    int read_index;
    int write_index;
};

