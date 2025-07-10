#pragma once

#include <functional>
#include <memory>
#include <stdio.h>
#include "common.h"

class TcpServer;
class TcpConnection;
class HttpRequest;
class HttpResponse;
class EventLoop;

class HttpServer{
public:
    DISALLOW_COPY_AND_MOVE(HttpServer);
    typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
    typedef std::function<void(const HttpRequest&, HttpResponse*)> HttpResponseCallback;
    
    HttpServer(EventLoop* loop, const char* ip, const int port);
    ~HttpServer();

    void HttpDefaultCallBack(const HttpRequest& request, HttpResponse* response);
    void setHttpCallback(const HttpResponseCallback& callback);

    void start();

    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn);
    void onRequest(const TcpConnectionPtr& conn, const HttpRequest& request);
    
    void setThreadNums(int thread_nums);
private:
    EventLoop* loop;
    std::unique_ptr<TcpServer> server;

    HttpResponseCallback response_callback;
};