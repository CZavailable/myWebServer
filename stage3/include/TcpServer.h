#pragma once
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>
#include "common.h"

class ThreadPool;
class EventLoop;
class Acceptor;
class TcpConnection;

class TcpServer
{
public:
    DISALLOW_COPY_AND_MOVE(TcpServer);
    explicit TcpServer(const char* ip, const int port);
    ~TcpServer();

    void setConnectionCallback(std::function<void(TcpConnection*)> const& callback);
    void setMessageCallback(std::function<void(TcpConnection*)> const& callback);
    
    void handleClose(int fd);
    void handleNewConnection(int fd);

    void start();
private:
    std::unique_ptr<EventLoop> mainReactor;
    std::unique_ptr<Acceptor> acceptor;
    std::unordered_map<int, TcpConnection*> connections;
    std::vector<std::unique_ptr<EventLoop>> subReactors;
    std::unique_ptr<ThreadPool> thpool;

    std::function<void(TcpConnection*)> onConnectionCallback;
    std::function<void(TcpConnection*)> onMessageCallback;
    int next_conn_id_;
};


