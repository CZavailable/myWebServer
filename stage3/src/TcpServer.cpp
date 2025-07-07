#include <functional>
#include <iostream>
#include "Acceptor.h"
#include "TcpConnection.h"
#include "ThreadPool.h"
#include "EventLoop.h"
#include "TcpServer.h"
#include <unistd.h>
#include <assert.h>

TcpServer::TcpServer(const char* ip, const int port) : next_conn_id_(1){ 
    mainReactor = std::make_unique<EventLoop>();
    acceptor = std::make_unique<Acceptor>(mainReactor.get(),ip,port);
    std::function<void(int)> cb = std::bind(&TcpServer::handleNewConnection, this, std::placeholders::_1);
    acceptor->setNewConnectionCallback(cb);

    int size = std::thread::hardware_concurrency();
    thpool = std::make_unique<ThreadPool>(size);
    for(int i = 0; i < size; ++i){
        std::unique_ptr<EventLoop> sub_reactor = std::make_unique<EventLoop>();
        subReactors.emplace_back(std::move(sub_reactor));
    }
}

TcpServer::~TcpServer(){
}

void TcpServer::start(){
    for(int i = 0; i < subReactors.size(); ++i){
        std::function<void()> sub_loop = std::bind(&EventLoop::loop, subReactors[i].get());
        thpool->add(std::move(sub_loop));
    }
    mainReactor->loop();
}


void TcpServer::setConnectionCallback(std::function<void(TcpConnection*)> const& callback){
    onConnectionCallback = std::move(callback);
}

void TcpServer::setMessageCallback(std::function<void(TcpConnection*)> const& callback){
    onMessageCallback = std::move(callback);
}

void TcpServer::handleNewConnection(int fd){
    assert(fd != -1);
    std::cout << "New connection fd: " << fd << std::endl;
    uint64_t random = fd % subReactors.size();

    TcpConnection* conn = new TcpConnection(subReactors[random].get(), fd, next_conn_id_);
    std::function<void(int)> cb = std::bind(&TcpServer::handleClose, this, std::placeholders::_1);
    
    conn->setDeleteConnectionCallback(cb);
    conn->setOnMessageCallback(onMessageCallback);
    connections[fd] = conn;

    ++next_conn_id_;
    if(next_conn_id_ == 1000){
        next_conn_id_ = 1;
    }
}

void TcpServer::handleClose(int fd){
    if(fd != -1){
        auto it = connections.find(fd);
        if(it != connections.end()){
            TcpConnection *conn = connections[fd];
            connections.erase(fd);
            // 移除epoll中对conn的监听
            conn->deleteConnectionChannel();
            // 关闭socket
            ::close(fd);  
            conn = nullptr;
        }
    }
}