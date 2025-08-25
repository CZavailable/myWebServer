#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <jsoncpp/json/json.h>
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpServer.h"
#include "EventLoop.h"
#include "Logging.h"
#include "AsyncLogging.h"

std::string readFile(const std::string& path) {
    std::ifstream is(path.c_str(), std::ifstream::in);

    is.seekg(0, is.end);

    int flength = is.tellg();

    is.seekg(0, is.beg);
    char* buffer = new char[flength];

    is.read(buffer, flength);
    std::string msg(buffer, flength);
    return msg;
}

// const std::string html = " <font color=\"red\">This is html!</font> ";
void HttpResponseCallback(const HttpRequest& request, HttpResponse* response)
{
    std::string url = request.getUrl();
    if(request.getMethod() == HttpRequest::Method::kGet) {
        
        if(url == "/"){
            std::string body = readFile("../static/index.html");
            response->setStatusCode(HttpResponse::HttpStatusCode::k200K);
            response->setBody(body);
            response->setContentType("text/html");
        }else if(url == "/mhw"){
            std::string body = readFile("../static/mhw.html");
            response->setStatusCode(HttpResponse::HttpStatusCode::k200K);
            response->setBody(body);
            response->setContentType("text/html");
        }else if(url == "/cat.jpg"){
            std::string body = readFile("../static/cat.jpg");
            response->setStatusCode(HttpResponse::HttpStatusCode::k200K);
            response->setBody(body);
            response->setContentType("image/jpeg");
        }else{
            response->setStatusCode(HttpResponse::HttpStatusCode::k404NotFound);
            response->setStatusMessage("Not Found");
            response->setBody("Sorry Not Found\n");
            response->setCloseConnection(true);
        }
    }
    else if(request.getMethod() == HttpRequest::Method::kPost) {
        if(url == "/login") {
            std::string rqbody = request.getBody();
            int usernamePos = rqbody.find("username=");
            int passwordPos = rqbody.find("password=");
            usernamePos += 9;
            passwordPos += 9;
            size_t usernameEndPos = rqbody.find('&', usernamePos);
            size_t passwordEndPos = rqbody.length();

            std::string username = rqbody.substr(usernamePos, usernameEndPos - usernamePos);
            std::string password = rqbody.substr(passwordPos, passwordEndPos - passwordPos);

            if(username == "cz") {
                response->setBody("login ok!\n");
            }
            else {
                response->setBody("error!/n");
            }
            response->setStatusCode(HttpResponse::HttpStatusCode::k200K);
            response->setStatusMessage("OK");
            response->setContentType("text/plain");
        }
    }
    else {
        response->setStatusCode(HttpResponse::HttpStatusCode::k400BadRequest);
        response->setStatusMessage("Bad Request");
        response->setCloseConnection(true);
    }
    return;
}

std::unique_ptr<AsyncLogging> asynclog;
void AsyncOutputFunc(const char* data, int len){
    asynclog->append(data, len);
}

void AsyncFlushFunc(){
    asynclog->flush();
}

int main(int argc, char *argv[]){

    asynclog = std::make_unique<AsyncLogging>();
    Logger::setOutput(AsyncOutputFunc);
    Logger::setFlush(AsyncFlushFunc);
    asynclog->start();

    int size = std::thread::hardware_concurrency() - 1;
    EventLoop *loop = new EventLoop();
    HttpServer *server = new HttpServer(loop,"192.168.40.129",1234,true);
    server->setHttpCallback(HttpResponseCallback);
    server->setThreadNums(size);
    server->start();
    
    return 0;
}