#pragma once

#include <string>
#include <utility>
#include <map>

class HttpResponse{
public:
    enum HttpStatusCode{
        kUnkonwn = 1,
        k100Continue = 100,
        k200K = 200,
        k400BadRequest = 400,
        k403Forbidden = 403,
        k404NotFound = 404,
        k500internalServerError = 500
    };
    HttpResponse(bool close_connection);
    ~HttpResponse();

    void setStatusCode(HttpStatusCode status_code);
    void setStatusMessage(const std::string& status_message);
    void setCloseConnection(bool close_connection);

    void setContentType(const std::string& content_type);
    void addHeader(const std::string& key, const std::string& value);

    void setBody(const std::string& body);
    std::string setMessage();
    bool isCloseConnection();
private:
    std::map<std::string, std::string> headers;
    HttpStatusCode status_code;
    std::string status_message;
    std::string body;
    bool close_connection;
};