#include "Buffer.h"

void Buffer::append(const char* _str, int _size){
    for(int i = 0; i < _size; ++i){
        if(_str[i] == '\0') break;
        buf.push_back(_str[i]);
    }
}

ssize_t Buffer::size() const{
    return buf.size();
}

const char* Buffer::c_str() const{
    return buf.c_str();
}

void Buffer::clear(){
    buf.clear();
}

const std::string& Buffer::getBuf() const{
    return buf;
}

void Buffer::setBuf(const char* _buf){
    std::string new_buf(_buf);
    buf.swap(new_buf);
}