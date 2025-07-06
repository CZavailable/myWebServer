#pragma once
#include <functional>

class EventLoop;
class Socket;
class Channel;
class Buffer;

class Connection
{
public:
    enum State{
        Invalid = 1,
        Handshaking,
        Connected,
        Closed,
        Failed,
    };
private:
    EventLoop *loop;
    Socket *sock;
    Channel *channel;
    Buffer *read_Buffer;
    Buffer *send_Buffer;
    State state;
    std::function<void(Socket* )> deleteConnectionCallback;
    std::function<void(Connection* )> onConnectionCallback;
    
    void readNonBlocking();
    void readBlocking();
    void writeNonBlocking();
    void writeBlocking();
public:

    Connection(EventLoop *_loop, Socket *_sock);
    ~Connection();
    
    void read();
    void write();

    void setDeleteConnectionCallback(std::function<void(Socket*)> const& callback);
    void setOnConnectionCallback(std::function<void(Connection*)> const& callback);

    State getState();
    void close();

    void setSendBuffer(const char*);
    Buffer* getSendBuffer();
    const char* sendBuffer();
    void getLineSendBuffer();
    Buffer* getReadBuffer();
    const char* readBuffer();

    Socket* getSocket();
    void onConnection(std::function<void()> fn);
};

