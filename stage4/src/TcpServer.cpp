#include <functional>
#include <iostream>
#include <memory>
#include <unistd.h>
#include <assert.h>
#include "Acceptor.h"
#include "TcpConnection.h"
#include "ThreadPool.h"
#include "EventLoop.h"
#include "TcpServer.h"
#include "CurrentThread.h"

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
        // 线程池中的每一个线程都在执行EventLoop中的loop函数
        thpool->add(std::move(sub_loop));
    }
    mainReactor->loop();
}


void TcpServer::setConnectionCallback(std::function<void(const std::shared_ptr<TcpConnection>&)> const& callback){
    onConnectionCallback = std::move(callback);
}

void TcpServer::setMessageCallback(std::function<void(const std::shared_ptr<TcpConnection>&)> const& callback){
    onMessageCallback = std::move(callback);
}

inline void TcpServer::handleNewConnection(int fd){
    assert(fd != -1);
    std::cout << "New connection fd: " << fd << std::endl;
    uint64_t random = fd % subReactors.size();

    // 采用shared_ptr管理TcpConnection的生命周期
    std::shared_ptr<TcpConnection> conn = std::make_shared<TcpConnection>(subReactors[random].get(), fd, next_conn_id_);
    // TcpConnection* conn = new TcpConnection(subReactors[random].get(), fd, next_conn_id_);
    std::function<void(const std::shared_ptr<TcpConnection>&)> cb = std::bind(&TcpServer::handleClose, this, std::placeholders::_1);
    conn->setOnConnectionCallback(onConnectionCallback);
    conn->setDeleteConnectionCallback(cb);
    conn->setOnMessageCallback(onMessageCallback);
    connections[fd] = conn;

    ++next_conn_id_;
    if(next_conn_id_ == 1000){
        next_conn_id_ = 1;
    }

    // 监听读事件
    conn->connectionEstablished();  // 新加入进TcpConnection的函数
}

inline void TcpServer::handleClose(const std::shared_ptr<TcpConnection>& conn){
    std::cout << "Thread " << CurrentThread::tid() << " TcpServer::handleClose" << std::endl;
    mainReactor->runOneFunc(std::bind(&TcpServer::handleCloseInLoop, this, conn));  // 新加入进EventLoop的函数
    // if(fd != -1){
    //     auto it = connections.find(fd);
    //     if(it != connections.end()){
    //         TcpConnection *conn = connections[fd];
    //         connections.erase(fd);
    //         // 移除epoll中对conn的监听
    //         conn->deleteConnectionChannel();
    //         // 关闭socket
    //         ::close(fd);  
    //         conn = nullptr;
    //     }
    // }
}

inline void TcpServer::handleCloseInLoop(const std::shared_ptr<TcpConnection>& conn){
    std::cout << "Thread " << CurrentThread::tid()  << " TcpServer::handleCloseInLoop - Remove connection id: " <<  conn->getId() << " and fd: " << conn->getFd() << std::endl;
    auto it = connections.find(conn->getFd());
    assert(it != connections.end());
    
    connections.erase(conn->getFd());

    EventLoop* loop = conn->getLoop();   // 新加入进TcpConnection的函数
    loop->queueOneFunc(std::bind(&TcpConnection::connectionDestructor, conn));  // 新加入进TcpConnection和EventLoop的函数

    // 移除epoll中对conn的监听
    // conn->deleteConnectionChannel();
    // 关闭socket
    // ::close(conn->getFd());  
    // conn = nullptr;
}