#pragma once
#include <map>
#include <vector>
#include <functional>

class ThreadPool;
class EventLoop;
class Socket;
class Acceptor;
class Connection;

class Server
{
private:
    EventLoop *mainReactor;
    Acceptor *acceptor;
    std::map<int, Connection*> connections;
    std::vector<EventLoop*> subReactors;
    ThreadPool* thpool;
    std::function<void(Connection*)> onConnectionCallback;

public:
    explicit Server(EventLoop*);
    ~Server();

    void onConnection(std::function<void(Connection *)> fn);
    void newConnection(Socket *sock);
    void deleteConnection(Socket *sock);
};


