#include <string>
#include <cstring>
#include <assert.h>
#include "Buffer.h"


Buffer::Buffer() : buffer(kInitalSize) , read_index(kPrePendIndex) , write_index(kPrePendIndex){}

Buffer::~Buffer(){}

char* Buffer::begin(){
    return &*buffer.begin();
}

const char* Buffer::begin() const{
    return &*buffer.begin();
}

char* Buffer::beginRead(){
    return begin() + read_index;
}

const char* Buffer::beginRead() const{
    return begin() + read_index;
}

char* Buffer::beginWrite(){
    return begin() + write_index;
}

const char* Buffer::beginWrite() const{
    return begin() + write_index;
}

void Buffer::append(const char* message){
    append(message, static_cast<int>(strlen(message)));
}

void Buffer::append(const char* message, int len){
    ensureWritableBytes(len);
    std::copy(message, message + len, beginWrite());
    write_index += len;
}

void Buffer::append(const std::string& message){
    append(message.data(), static_cast<int>(message.size()));
}

int Buffer::readableBytes() const{
    return write_index - read_index;
}

int Buffer::writableBytes() const{
    return static_cast<int>(buffer.size()) - write_index;   
}

int Buffer::prependaBlebytes() const{
    return read_index;
}

char* Buffer::peek(){
    return beginRead();
}

const char* Buffer::peek() const{
    return beginRead();
}

std::string Buffer::peekAsString(int len){
    return std::string(beginRead(), beginRead() + len);
}

std::string Buffer::peekAllAsString(){
    return std::string(beginRead(), beginWrite());
}

void Buffer::retrieve(int len){
    assert(readableBytes() > len);
    if(len + read_index < write_index){
        read_index += len;
    }
    else{
        retrieveAll();
    }
}

void Buffer::retrieveAll(){
    write_index = kPrePendIndex;
    read_index = write_index;
}

void Buffer::retrieveUtil(const char* end){
    assert(beginWrite() >= end);
    read_index += static_cast<int>(end - beginRead());
}

std::string Buffer::retrieveAsString(int len){
    assert(read_index + len <= write_index);
    std::string ret = std::move(peekAsString(len));
    retrieve(len);
    return ret;
}

std::string Buffer::retrieveUtilAsString(const char* end){
    assert(beginWrite() >= end);
    std::string ret = std::move(peekAsString(static_cast<int>(end - beginRead())));
    retrieveUtil(end);
    return ret;
}

std::string Buffer::retrieveAllAsString(){
    assert(readableBytes() > 0);
    std::string ret = std::move(peekAllAsString());
    retrieveAll();
    return ret;
}

void Buffer::ensureWritableBytes(int len){
    if(writableBytes() >= len){
        return;
    }
    if(writableBytes() + prependaBlebytes() >= kPrePendIndex + len){
        std::copy(beginRead(), beginWrite(), begin() + kPrePendIndex);
        write_index = kPrePendIndex + readableBytes();
        read_index = kPrePendIndex;
    }
    else{
        buffer.resize(write_index + len);
    }
}

// ssize_t Buffer::size() const{
//     return buf.size();
// }

// const char* Buffer::c_str() const{
//     return buf.c_str();
// }

// void Buffer::clear(){
//     buf.clear();
// }

// const std::string& Buffer::getBuf() const{
//     return buf;
// }

// void Buffer::setBuf(const char* _buf){
//     std::string new_buf(_buf);
//     buf.swap(new_buf);
// }