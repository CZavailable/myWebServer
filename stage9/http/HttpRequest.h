#pragma once
#include <string>
#include <map>

class HttpRequest{
public:
    enum Method{
        kInvalid = 0,
        kGet,
        kPost,
        kHead,
        kPut,
        kDelete
    };
    enum Version{
        kUnknown = 0,
        kHttp10,
        kHttp11
    };

    HttpRequest();
    ~HttpRequest();

    // http版本
    void setVersion(const std::string& ver);
    Version getVersion() const;
    std::string getVersionString() const;

    // 请求方法
    bool setMethod(const std::string& method);
    Method getMethod() const;
    std::string getMethodString() const;

    // url
    void setUrl(const std::string& url);
    const std::string& getUrl() const;

    // 请求参数
    void setRequestParams(const std::string& key, const std::string& value);
    std::string getRequestValue(const std::string& key) const;
    const std::map<std::string, std::string>& getRequestParams() const;

    // 协议
    void setProtocol(const std::string& str);
    const std::string& getProtocol() const;

    // 请求头
    void addHeader(const std::string& field, const std::string& value);
    std::string getHeaderValue(const std::string& field) const;
    const std::map<std::string, std::string>& getHeader() const;

    // 请求体
    void setBody(const std::string& str);
    const std::string& getBody() const;

private:
    Method method;
    Version version;

    std::map<std::string, std::string> request_params;
    std::string url;
    std::string protocol;
    std::map<std::string, std::string> headers;
    std::string body;
};