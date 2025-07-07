# 将多线程Reactor改造为主从Reactor模型，将线程池模块从EventLoop模块中抽离出来，将其交给Server类管理
# 将头文件与源文件分别放在include文件夹和src文件夹,测试的代码都放在test文件夹中

# 用智能指针管理资源,但是handleClose 后未从 epoll 中注销 fd，可能导致段错误

TcpConnection::~TcpConnection(){
    // 不再手动 close(connfd)，统一由 handleClose() 管理
}
~TcpConnection()部分逻辑还未解决，主要是TcpConnection类由裸指针管理，又不能在handleclose中delete，否则会造成段错误，因为handleclose是其成员函数，所以这一块可能会造成内存泄漏，也应由智能指针来管理，再下个阶段解决

# 这个版本通过用智能指针管理类，并且用户通过回调函数的形式自定义服务器处理数据的逻辑，这里实现了简单的回声服务器，经测试，QPS可以达到上万