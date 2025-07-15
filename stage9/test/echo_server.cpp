#include "TcpServer.h"
#include "TcpConnection.h"
#include "EventLoop.h"
#include "Buffer.h"
#include "Acceptor.h"
#include "CurrentThread.h"
#include "ThreadPool.h"
#include <iostream>
#include <functional>
#include <vector>
#include <arpa/inet.h>

class echoServer{
public:
    echoServer(EventLoop* loop, const char* ip, const int port) : server_(loop, ip, port){
        server_.setConnectionCallback(std::bind(&echoServer::onConnection, this, std::placeholders::_1));
        server_.setMessageCallback(std::bind(&echoServer::onMessage, this, std::placeholders::_1));
    }

    ~echoServer(){}

    void start(){
        server_.start();
    }

    void setThreadNums(int thread_nums){
        server_.setThreadNums(thread_nums);
    }

    void onConnection(const std::shared_ptr<TcpConnection>& conn){
        int client_fd = conn->getFd();
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        getpeername(client_fd, (sockaddr*)&client_addr, &client_addr_len);
        std::cout << "Thread "
                  << CurrentThread::tid()
                  << " EchoServer::OnNewConnection : new connection "
                  << "[fd#" << client_fd << "]"
                  << " from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port)
                  << std::endl;
    }

    void onMessage(const std::shared_ptr<TcpConnection>& conn){
        if (conn->getState() == TcpConnection::ConnectionState::Connected){
            std::cout << "Thread " << CurrentThread::tid() << " Message from clent " << conn->read_buf()->peekAllAsString().c_str() << std::endl;
            conn->send(conn->read_buf()->peekAllAsString().c_str());
            // conn->handleClose();
        }
    }
private:
    TcpServer server_;
};


int main(int argc, char* argv[]) {
    EventLoop* loop = new EventLoop();
    echoServer* server = new echoServer(loop,"192.168.40.129",1234);
    server->setThreadNums(std::thread::hardware_concurrency());
    server->start();
    return 0;
}
