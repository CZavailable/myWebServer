#include <iostream>
#include <string>
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpServer.h"
#include "EventLoop.h"

const std::string html = " <font color=\"red\">This is html!</font> ";
void HttpResponseCallback(const HttpRequest& request, HttpResponse* response)
{
    if(request.getMethod() != HttpRequest::Method::kGet){
        response->setStatusCode(HttpResponse::HttpStatusCode::k400BadRequest);
        response->setStatusMessage("Bad Request");
        response->setCloseConnection(true);
    }

    {
        std::string url = request.getUrl();
        if(url == "/"){
            response->setStatusCode(HttpResponse::HttpStatusCode::k200K);
            response->setBody(html);
            response->setContentType("text/html");
        }else if(url == "/hello"){
            response->setStatusCode(HttpResponse::HttpStatusCode::k200K);
            response->setBody("hello world\n");
            response->setContentType("text/plain");
        }else if(url == "/favicon.ico"){
            response->setStatusCode(HttpResponse::HttpStatusCode::k200K);
        }else{
            response->setStatusCode(HttpResponse::HttpStatusCode::k404NotFound);
            response->setStatusMessage("Not Found");
            response->setBody("Sorry Not Found\n");
            response->setCloseConnection(true);
        }
    }
    return;
}

int main(int argc, char *argv[]){
    int size = std::thread::hardware_concurrency();
    EventLoop *loop = new EventLoop();
    HttpServer *server = new HttpServer(loop,"192.168.40.129",1234);
    server->setHttpCallback(HttpResponseCallback);
    server->setThreadNums(size);
    server->start();
    
    return 0;
}