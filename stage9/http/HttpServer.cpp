#include <arpa/inet.h>
#include <functional>
#include <iostream>
#include "HttpServer.h"
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "HttpContext.h"
#include "Acceptor.h"
#include "TcpServer.h"
#include "TcpConnection.h"
#include "Buffer.h"
#include "EventLoop.h"
#include "CurrentThread.h"
#include "TimeStamp.h"

HttpServer::HttpServer(EventLoop* loop, const char* ip, const int port, bool auto_close_conn_) : loop(loop), auto_close_conn(auto_close_conn_){
    server = std::make_unique<TcpServer>(this->loop, ip, port);
    server->setConnectionCallback(std::bind(&HttpServer::onConnection, this, std::placeholders::_1));
    server->setMessageCallback(std::bind(&HttpServer::onMessage, this, std::placeholders::_1));

    setHttpCallback(std::bind(&HttpServer::HttpDefaultCallBack, this, std::placeholders::_1, std::placeholders::_2));
}

HttpServer::~HttpServer(){}

void HttpServer::HttpDefaultCallBack(const HttpRequest& request, HttpResponse* response){
    response->setStatusCode(HttpResponse::HttpStatusCode::k404NotFound);
    response->setStatusMessage("Not Found");
    response->setCloseConnection(true);
}

void HttpServer::onConnection(const TcpConnectionPtr& conn){
    int client_fd = conn->getFd();
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    getpeername(client_fd, (sockaddr*)&client_addr, &client_addr_len);

    std::cout << "Thread "
              << CurrentThread::tid()
              << " HttpServer::OnNewConnection "
              << "from "
              << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port)
              << std::endl;

    if(auto_close_conn){
        loop->runAfter(AUTOCLOSETIMEOUT, std::move(std::bind(&HttpServer::activeCloseConn, this, std::weak_ptr<TcpConnection>(conn))));
    }
}

void HttpServer::onMessage(const TcpConnectionPtr& conn){
    if(conn->getState() == TcpConnection::ConnectionState::Connected){
        // 保存最近一次的活跃时间
        if(auto_close_conn){
            conn->updateTimeStamp(TimeStamp::now());
        }

        HttpContext* context = conn->getContext();
        if(!context->paraseRequest(conn->read_buf()->retrieveAllAsString())){
            conn->send("HTTP/1.1 400 Bad Request\r\n\r\n");
            conn->handleClose();
        }

        if(context->getCompleteRequest()){
            onRequest(conn, *context->getRequest());
            context->resetContextStatus();
        }

    }
}

void HttpServer::setHttpCallback(const HttpServer::HttpResponseCallback& callback){
    response_callback = std::move(callback);
}

void HttpServer::onRequest(const TcpConnectionPtr& conn, const HttpRequest& request){
    std::string connection_state = request.getHeaderValue("Connection");
    bool close = (connection_state == "Close" || (request.getVersion() == HttpRequest::Version::kHttp10 && connection_state != "keep-alive"));
    HttpResponse response(close);
    response_callback(request, &response);

    conn->send(response.setMessage().c_str());

    if(response.isCloseConnection()){
        conn->handleClose();
    }
}

void HttpServer::start(){
    server->start();
}

void HttpServer::setThreadNums(int thread_nums){
    server->setThreadNums(thread_nums);
}

void HttpServer::activeCloseConn(std::weak_ptr<TcpConnection>& connection){
    TcpConnectionPtr conn = connection.lock();
    if(conn){
        if(TimeStamp::addTime(conn->getTimeStamp(), AUTOCLOSETIMEOUT) < TimeStamp::now()){
            conn->handleClose();
        }
        else{
            loop->runAfter(AUTOCLOSETIMEOUT, std::move(std::bind(&HttpServer::activeCloseConn, this, connection)));
        }
    }
}