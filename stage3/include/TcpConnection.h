#pragma once
#include <functional>
#include <memory>
#include <string>
#include "common.h"

class EventLoop;
class Channel;
class Buffer;

class TcpConnection
{
public:
    DISALLOW_COPY_AND_MOVE(TcpConnection);
    enum ConnectionState{
        Invalid = 1,
        Connected,
        Disconnected
    };
    TcpConnection(EventLoop *_loop, int connfd, int connid);
    ~TcpConnection();
    
    void read();
    void write();

    void setDeleteConnectionCallback(std::function<void(int)> const& callback);
    void setOnMessageCallback(std::function<void(TcpConnection*)> const& callback);
    void handleMessage();
    void handleClose();
    void deleteConnectionChannel();

    void setSendBuf(const char* str);
    Buffer* read_buf();
    Buffer* send_buf();

    void send(const std::string& msg);
    void send(const char* msg, int len);
    void send(const char* msg);

    EventLoop* getLoop() const;
    ConnectionState getState() const;
    int getFd() const;
    int getId() const;

private:
    EventLoop* loop;
    int connfd;
    int connid;
    std::unique_ptr<Channel> channel;
    std::unique_ptr<Buffer> read_Buffer;
    std::unique_ptr<Buffer> send_Buffer;
    ConnectionState state;
    std::function<void(int)> deleteConnectionCallback;
    std::function<void(TcpConnection*)> onMessageCallback;
    
    void readNonBlocking();
    void readBlocking();
    void writeNonBlocking();
    void writeBlocking();
};

