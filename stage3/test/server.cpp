#include "TcpServer.h"
#include "TcpConnection.h"
#include "EventLoop.h"
#include "Buffer.h"
#include "Acceptor.h"
#include <iostream>
#include <memory>

int main() {

    std::unique_ptr<TcpServer> server = std::make_unique<TcpServer>("192.168.40.129",1234);
    server->setMessageCallback([](TcpConnection* conn){
        // conn->read();
        if (conn->getState() == TcpConnection::ConnectionState::Disconnected) {
            conn->handleClose();
            return;
        }
        std::cout << "Message from client " << conn->getId() << ": " << conn->read_buf()->c_str() << std::endl;
        conn->send(conn->read_buf()->c_str());
    });

    server->start();

    return 0;
}
