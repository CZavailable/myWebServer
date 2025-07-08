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

    void setConnectionCallback(std::function<void(const std::shared_ptr<TcpConnection>&)> const& callback);
    void setMessageCallback(std::function<void(const std::shared_ptr<TcpConnection>&)> const& callback);
    
    inline void handleClose(const std::shared_ptr<TcpConnection>&);
    inline void handleCloseInLoop(const std::shared_ptr<TcpConnection>&);
    inline void handleNewConnection(int fd);

    void start();
private:
    std::unique_ptr<EventLoop> mainReactor;
    std::unique_ptr<Acceptor> acceptor;
    std::unordered_map<int,std::shared_ptr<TcpConnection>> connections;
    std::vector<std::unique_ptr<EventLoop>> subReactors;
    std::unique_ptr<ThreadPool> thpool;

    std::function<void(const std::shared_ptr<TcpConnection>&)> onConnectionCallback;
    std::function<void(const std::shared_ptr<TcpConnection>&)> onMessageCallback;
    int next_conn_id_;
};


