#pragma once
#include <arpa/inet.h>

class InetAddress
{
private:
    struct sockaddr_in addr;
public:
    InetAddress();
    InetAddress(const char* _ip, uint16_t _port);
    ~InetAddress();

    void setInetAddr(sockaddr_in _addr);
    uint16_t getPort();
    sockaddr_in getAddr();
};

