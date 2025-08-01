#include <memory>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstring>
#include "HttpContext.h"
#include "HttpRequest.h"

HttpContext::HttpContext() : state(HttpRequestParaseState::START){
    request = std::make_unique<HttpRequest>();
}

HttpContext::~HttpContext(){}

bool HttpContext::getCompleteRequest(){
    return state == HttpRequestParaseState::COMPLETE;
}

void HttpContext::resetContextStatus(){
    state = HttpRequestParaseState::START;
}

HttpRequest* HttpContext::getRequest(){
    return request.get();
}

bool HttpContext::paraseRequest(const std::string& msg){
    return paraseRequest(msg.data(), static_cast<int>(msg.size()));
}

bool HttpContext::paraseRequest(const char* begin){
    return paraseRequest(begin, static_cast<int>(strlen(begin)));
}

bool HttpContext::paraseRequest(const char* begin, int size){
    char* start = const_cast<char*>(begin);
    char* end = start;
    char* colon = end;
    while(state != HttpRequestParaseState::kINVALID
       && state != HttpRequestParaseState::COMPLETE
       && end - begin <= size){
        char ch = *end;
        switch(state){
            case HttpRequestParaseState::START:{
                if(ch == CR || ch == LF || isblank(ch)){
                    // 遇到空格，换行和回车都继续
                }
                else if(isupper(ch)){
                    // 遇到大写字母，说明遇到了METHOD
                    state = HttpRequestParaseState::METHOD;
                }
                else{
                    state = HttpRequestParaseState::kINVALID;
                }
                break;
            }
            case HttpRequestParaseState::METHOD:{
                if(isupper(ch)){
                    // 如果是大写字母，则继续
                }
                else if(isblank(ch)){
                    // 遇到空格表明，METHOD方法解析结束，当前处于即将解析URL，start进入下一个位置
                    request->setMethod(std::string(start, end));
                    state = HttpRequestParaseState::BEFORE_URL;
                    start = end + 1;
                }
                else{
                    state = HttpRequestParaseState::kINVALID;
                }
                break;
            }
            case HttpRequestParaseState::BEFORE_URL:{
                // 对请求连接前的处理，请求连接以'/'开头
                if(ch == '/'){
                    state = HttpRequestParaseState::IN_URL;
                }
                else if(isblank(ch)){

                }
                else{
                    state = HttpRequestParaseState::kINVALID;
                }
                break;
            }
            case HttpRequestParaseState::IN_URL:{
                // 进入url中
                if(ch == '?'){
                    // 当遇到?时，表明进入了request params的处理
                    request->setUrl(std::string(start, end));
                    start = end + 1;
                    state = HttpRequestParaseState::BEFORE_URL_PARAM_KEY;
                }
                else if(isblank(ch)){
                    request->setUrl(std::string(start, end));
                    start = end + 1;
                    state = HttpRequestParaseState::BEFORE_PROTOCOL;
                }
                break;
            }
            case HttpRequestParaseState::BEFORE_URL_PARAM_KEY:{
                if(isblank(ch) || ch == CR || ch == LF){
                    state = HttpRequestParaseState::kINVALID;
                }
                else{
                    state = HttpRequestParaseState::URL_PARAM_KEY;
                }
                break;
            }
            case HttpRequestParaseState::URL_PARAM_KEY:{
                if(ch == '='){
                    // 遇到= 说明key解析完成
                    colon = end;
                    state = HttpRequestParaseState::BEFORE_URL_PARAM_VALUE;
                }
                else if(isblank(ch)){
                    state = HttpRequestParaseState::kINVALID;
                }
                break;
            }
            case HttpRequestParaseState::BEFORE_URL_PARAM_VALUE:{
                if(isblank(ch) || ch == CR || ch == LF){
                    state = HttpRequestParaseState::kINVALID;
                }
                else{
                    state = HttpRequestParaseState::URL_PARAM_KEY;
                }
                break;
            }
            case HttpRequestParaseState::URL_PARAM_VALUE:{
                if(ch == '&'){
                    state = HttpRequestParaseState::BEFORE_URL_PARAM_KEY;
                    request->setRequestParams(std::string(start,colon), std::string(colon + 1, end));
                    start = end + 1;
                }
                else if(isblank(ch)){
                    // 遇到空格，说明解析结束
                    request->setRequestParams(std::string(start, colon), std::string(colon + 1, end));
                    start = end + 1;
                    state = HttpRequestParaseState::BEFORE_PROTOCOL;
                }
                break;
            }
            case HttpRequestParaseState::BEFORE_PROTOCOL:{
                if(isblank(ch)){

                }
                else{
                    state = HttpRequestParaseState::PROTOCOL;
                }
                break;
            }
            case HttpRequestParaseState::PROTOCOL:{
                if(ch == '/'){
                    request->setProtocol(std::string(start, end));
                    start = end + 1;
                    state = HttpRequestParaseState::BEFORE_VERSION;
                }
                else{

                }
                break;
            }
            case HttpRequestParaseState::BEFORE_VERSION:{
                if(isdigit(ch)){
                    state = HttpRequestParaseState::VERSION;
                }
                else{
                    state = HttpRequestParaseState::kINVALID;
                }
                break;
            }
            case HttpRequestParaseState::VERSION:{
                if(ch == CR){
                    request->setVersion(std::string(start,end));
                    start = end + 1;
                    state = HttpRequestParaseState::WHEN_CR;
                }
                else if(isdigit(ch) || ch == '.'){

                }
                else{
                    state = HttpRequestParaseState::kINVALID;
                }
                break;
            }
            case HttpRequestParaseState::HEADER_KEY:{
                if(ch == ':'){
                    colon = end;
                    state = HttpRequestParaseState::HEADER_VALUE;
                }
                break;
            }
            case HttpRequestParaseState::HEADER_VALUE:{
                if(isblank(ch)){

                }
                else if(ch == CR){
                    request->addHeader(std::string(start, colon), std::string(colon + 2, end));
                    start = end + 1;
                    state = HttpRequestParaseState::WHEN_CR;
                }
                break;
            }
            case HttpRequestParaseState::WHEN_CR:{
                if(ch == LF){
                    // 如果遇到了'\n'之后遇到了'\r'，那就意味着这一行结束了
                    start = end + 1;
                    state = HttpRequestParaseState::CR_LF;
                }else{
                    state = HttpRequestParaseState::kINVALID;
                }
                break;
            }
            case HttpRequestParaseState::CR_LF:{
                if(ch == CR){
                    // 说明遇到了空行，大概率时结束了
                    state = HttpRequestParaseState::CR_LF_CR;
                    //start  = end + 1;
                    //std::cout << "a:" << (*start == '\n') << std::endl;
                    //std::cout << "b:" << (*end == '\r') << std::endl;
                }else if(isblank(ch)){
                    state = HttpRequestParaseState::kINVALID;
                }else{
                    state = HttpRequestParaseState::HEADER_KEY;
                }
                break;
            }
            case HttpRequestParaseState::CR_LF_CR:{
                if(ch == LF){
                    // 这就意味着遇到了空行，要进行解析请求体了
                    if(request->getHeader().count("Content-Length")){
                        if(atoi(request->getHeaderValue("Content-Length").c_str()) > 0){
                            state = HttpRequestParaseState::BODY;
                        }else{
                            state = HttpRequestParaseState::COMPLETE;
                        }
                    }else{
                        if(end - begin < size){
                            state = HttpRequestParaseState::BODY;
                        }else{
                            state = HttpRequestParaseState::COMPLETE;
                        }
                    }
                    start = end + 1;
                }else{
                    state = HttpRequestParaseState::kINVALID;
                }
                break;
            }
            case HttpRequestParaseState::BODY:{
                int bodylength = size - (end - begin);
                request->setBody(std::string(start, start + bodylength));
                state = HttpRequestParaseState::COMPLETE;
                break;
            }

            default:
                state = HttpRequestParaseState::kINVALID;
                break;
        }
        end++;
    }
    return state == HttpRequestParaseState::COMPLETE;
}