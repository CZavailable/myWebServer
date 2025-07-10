#pragma once
#include <functional>
#include <memory>
#include <string>
#include "common.h"

class EventLoop;
class Channel;
class Buffer;
class HttpContext;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
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

    void setDeleteConnectionCallback(std::function<void(const std::shared_ptr<TcpConnection>&)> const& callback);
    void setOnMessageCallback(std::function<void(const std::shared_ptr<TcpConnection>&)> const& callback);
    void setOnConnectionCallback(std::function<void(const std::shared_ptr<TcpConnection>&)> const& callback);
    void handleMessage();
    void handleClose();

    void connectionEstablished();
    void connectionDestructor();
    // void deleteConnectionChannel();

    void setSendBuf(const char* str);
    Buffer* read_buf();
    Buffer* send_buf();

    void send(const std::string& msg);
    void send(const char* msg, int len);
    void send(const char* msg);

    EventLoop* getLoop() const;
    ConnectionState getState() const;
    HttpContext* getContext() const;
    int getFd() const;
    int getId() const;

private:
    EventLoop* loop;
    int connfd;
    int connid;
    ConnectionState state;
    
    std::unique_ptr<Channel> channel;
    std::unique_ptr<Buffer> read_Buffer;
    std::unique_ptr<Buffer> send_Buffer;
    std::unique_ptr<HttpContext> context;
    
    std::function<void(const std::shared_ptr<TcpConnection>&)> deleteConnectionCallback;
    std::function<void(const std::shared_ptr<TcpConnection>&)> onMessageCallback;
    std::function<void(const std::shared_ptr<TcpConnection>&)> onConnectionCallback;
    
    void readNonBlocking();
    void readBlocking();
    void writeNonBlocking();
    void writeBlocking();
};

