#include <string>
#include "HttpResponse.h"

HttpResponse::HttpResponse(bool close_connection)
    : status_code(HttpStatusCode::kUnkonwn), close_connection(close_connection){}

HttpResponse::~HttpResponse(){}

void HttpResponse::setStatusCode(HttpStatusCode status_code){
    this->status_code = status_code;
}

void HttpResponse::setStatusMessage(const std::string& status_message){
    this->status_message = std::move(status_message);
}

void HttpResponse::setCloseConnection(bool close_connection){
    this->close_connection = close_connection;
}

void HttpResponse::setContentType(const std::string& content_type){
    addHeader("Content-Type",content_type);
}

void HttpResponse::addHeader(const std::string& key, const std::string& value){
    headers[key] = value;
}

void HttpResponse::setBody(const std::string& body){
    this->body = std::move(body);
}

bool HttpResponse::isCloseConnection(){
    return close_connection;
}

std::string HttpResponse::setMessage(){
    std::string message;
    message += ("HTTP/1.1 " + std::to_string(status_code) + " " +
                status_message + "\r\n");
    if(close_connection){
        message += ("Connection: close\r\n");
    }
    else{
        message += ("Content-Length: " + std::to_string(body.size()) + "\r\n");
        message += ("Connection: Keep-Alive\r\n");
    }

    message += "\r\n";
    message += body; 

    return message;
}