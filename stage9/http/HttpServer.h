#pragma once
// 自动关闭的时间，以秒为单位
#define AUTOCLOSETIMEOUT 5

#include <functional>
#include <memory>
#include <stdio.h>
#include "common.h"

class TcpServer;
class TcpConnection;
class HttpRequest;
class HttpResponse;
class EventLoop;
class TimeStamp;

class HttpServer{
public:
    DISALLOW_COPY_AND_MOVE(HttpServer);
    typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
    typedef std::function<void(const HttpRequest&, HttpResponse*)> HttpResponseCallback;
    
    HttpServer(EventLoop* loop, const char* ip, const int port, bool auto_close_conn_);
    ~HttpServer();

    void HttpDefaultCallBack(const HttpRequest& request, HttpResponse* response);
    void setHttpCallback(const HttpResponseCallback& callback);

    void start();

    void onConnection(const TcpConnectionPtr& conn);
    void onMessage(const TcpConnectionPtr& conn);
    void onRequest(const TcpConnectionPtr& conn, const HttpRequest& request);
    
    void setThreadNums(int thread_nums);

    void activeCloseConn(std::weak_ptr<TcpConnection>& conn);
private:
    EventLoop* loop;
    std::unique_ptr<TcpServer> server;

    bool auto_close_conn;
    HttpResponseCallback response_callback;
};