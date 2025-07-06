#include "Server.h"
#include "Socket.h"
#include "Acceptor.h"
#include "Connection.h"
#include "ThreadPool.h"
#include "EventLoop.h"
#include <unistd.h>
#include <functional>
#include <assert.h>

Server::Server(EventLoop *_loop) : mainReactor(_loop), acceptor(nullptr){ 
    acceptor = new Acceptor(mainReactor);
    std::function<void(Socket*)> cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
    acceptor->setNewConnectionCallback(cb);

    int size = static_cast<int>(std::thread::hardware_concurrency());
    thpool = new ThreadPool(size);
    for(int i = 0; i < size; ++i){
        subReactors.push_back(new EventLoop());
    }

    for(int i = 0; i < size; ++i){
        std::function<void()> sub_loop = std::bind(&EventLoop::loop, subReactors[i]);
        thpool->add(std::move(sub_loop));
    }
}

Server::~Server(){
    delete acceptor;
    delete thpool;
}

void Server::onConnection(std::function<void(Connection *)> fn){
    onConnectionCallback = std::move(fn);
}

void Server::newConnection(Socket *sock){
    assert(sock->getFd() != -1);
    uint64_t random = sock->getFd() % subReactors.size();
    Connection *conn = new Connection(subReactors[random], sock);
    std::function<void(Socket *sock)> cb = std::bind(&Server::deleteConnection, this, std::placeholders::_1);
    conn->setDeleteConnectionCallback(cb);
    conn->setOnConnectionCallback(onConnectionCallback);
    connections[sock->getFd()] = conn;
}

void Server::deleteConnection(Socket *sock){
    int sockfd = sock->getFd();
    if(sockfd != -1){
        auto it = connections.find(sockfd);
        if(it != connections.end()){
            Connection *conn = connections[sockfd];
            connections.erase(sockfd);
            // close(sockfd);       //正常
            delete conn;         //会Segmant fault
            conn = nullptr;
        }
    }
}