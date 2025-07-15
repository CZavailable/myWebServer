#include <map>
#include <string>
#include <iostream>
#include "HttpRequest.h"

HttpRequest::HttpRequest() : method(kInvalid), version(kUnknown){}

HttpRequest::~HttpRequest(){};

void HttpRequest::setVersion(const std::string& ver){
    if(ver == "1.0"){
        version = Version::kHttp10;
    }
    else if(ver == "1.1"){
        version = Version::kHttp11;
    }
    else{
        version = Version::kUnknown;
    }
}

HttpRequest::Version HttpRequest::getVersion() const{
    return version;
}

std::string HttpRequest::getVersionString() const{
    std::string ver;
    if(version == Version::kHttp10){
        ver = "http1.0";
    }
    else if(version == Version::kHttp11){
        ver = "http1.1";
    }
    else{
        ver = "unknown";
    }
    return ver;
}

bool HttpRequest::setMethod(const std::string& _method){
    if(_method == "GET"){
        method = Method::kGet;
    }
    else if(_method == "POST"){
        method = Method::kPost;
    }
    else if(_method == "HEAD"){
        method = Method::kHead;
    }
    else if(_method == "PUT"){
        method = Method::kPut;
    }
    else if(_method == "Delete"){
        method = Method::kDelete;
    }
    return method != kInvalid;
}

HttpRequest::Method HttpRequest::getMethod() const{
    return method;
}

std::string HttpRequest::getMethodString() const{
    std::string _method;
    if(method == Method::kGet){
        _method = "GET";
    }
    else if(method == Method::kPost){
        _method = "POST";
    }
    else if(method == Method::kHead){
        _method = "HEAD";
    }
    else if(method == Method::kPut){
        _method = "PUT";
    }
    else if(method == Method::kDelete){
        _method = "Delete";
    }
    else{
        _method = "Invalid";
    }
    return _method;
}

void HttpRequest::setUrl(const std::string& url){
    this->url = std::move(url);
}

const std::string& HttpRequest::getUrl() const{
    return url;
}

void HttpRequest::setRequestParams(const std::string& key, const std::string& value){
    request_params[key] = value;
}

std::string HttpRequest::getRequestValue(const std::string& str) const{
    auto it = request_params.find(str);
    return (it == request_params.end() ? "" : it->second);
}

const std::map<std::string, std::string>& HttpRequest::getRequestParams() const{
    return request_params;
}

void HttpRequest::setProtocol(const std::string& str){
    protocol = std::move(str);
}

const std::string& HttpRequest::getProtocol() const{
    return protocol;
}

void HttpRequest::addHeader(const std::string& field, const std::string& value){
    headers[field] = value;
}
std::string HttpRequest::getHeaderValue(const std::string& field) const{
    auto it = headers.find(field);
    return (it == headers.end() ? "" : it->second);
}

const std::map<std::string, std::string>& HttpRequest::getHeader() const{
    return headers;
}

void HttpRequest::setBody(const std::string& str){
    body = std::move(str);
}

const std::string& HttpRequest::getBody() const{
    return body;
}