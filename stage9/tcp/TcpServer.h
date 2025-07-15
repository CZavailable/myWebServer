#pragma once
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>
#include "common.h"

class EventLoopThreadPool;
class EventLoop;
class Acceptor;
class TcpConnection;

class TcpServer
{
public:
    DISALLOW_COPY_AND_MOVE(TcpServer);
    explicit TcpServer(EventLoop* loop ,const char* ip, const int port);
    ~TcpServer();

    void setConnectionCallback(std::function<void(const std::shared_ptr<TcpConnection>&)> const& callback);
    void setMessageCallback(std::function<void(const std::shared_ptr<TcpConnection>&)> const& callback);
    
    inline void handleClose(const std::shared_ptr<TcpConnection>&);
    inline void handleCloseInLoop(const std::shared_ptr<TcpConnection>&);
    inline void handleNewConnection(int fd);

    void start();
    void setThreadNums(int thread_nums);
private:
    EventLoop* mainReactor;
    std::unique_ptr<Acceptor> acceptor;
    std::unordered_map<int,std::shared_ptr<TcpConnection>> connections;
    std::vector<std::unique_ptr<EventLoop>> subReactors;
    std::unique_ptr<EventLoopThreadPool> thread_pool_;

    std::function<void(const std::shared_ptr<TcpConnection>&)> onConnectionCallback;
    std::function<void(const std::shared_ptr<TcpConnection>&)> onMessageCallback;
    int next_conn_id_;
};


