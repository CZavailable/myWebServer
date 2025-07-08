# 将多线程Reactor改造为主从Reactor模型，将线程池模块从EventLoop模块中抽离出来，将其交给Server类管理
# 将头文件与源文件分别放在include文件夹和src文件夹,测试的代码都放在test文件夹中

# 用智能指针管理资源,但是handleClose 后未从 epoll 中注销 fd，可能导致段错误

TcpConnection::~TcpConnection(){
    // 不再手动 close(connfd)，统一由 handleClose() 管理
}
~TcpConnection()部分逻辑还未解决，主要是TcpConnection类由裸指针管理，又不能在handleclose中delete，否则会造成段错误，因为handleclose是其成员函数，所以这一块可能会造成内存泄漏，也应由智能指针来管理.

在这个版本解决这个问题：

✅ 改进 1：用 shared_ptr 管理 TcpConnection 生命周期
🎯 目的：
避免悬垂指针或过早析构，确保连接存活直到事件处理完。

🔧 具体实现：
TcpConnection 继承 enable_shared_from_this<TcpConnection>，确保可通过成员函数获取 shared_ptr<TcpConnection> self = shared_from_this();。

在 TcpServer::HandleNewConnection() 中使用 std::make_shared<TcpConnection>() 创建连接对象。

将该 shared_ptr 存入 connectionsMap_，引用计数 +1。

在传递回调（如 onConnect_）中统一使用 shared_ptr<TcpConnection>，保证生命周期安全。

✅ 改进 2：通过 Channel::tie() + weak_ptr 在事件触发时提升引用计数
🎯 目的：
确保在 HandleEvent() 中 TcpConnection 仍然活着，不被提早销毁。

🔧 实现机制：
Channel 内部持有 weak_ptr<void> 类型的 tie_ 成员；

在 TcpConnection::ConnectionEstablished() 中，调用 channel_->Tie(shared_from_this());；

Channel::HandleEvent() 首先执行：

cpp
复制
编辑
if (tie_) {
  auto guard = tie_.lock();  // 提升引用计数
  if (guard) {
    HandleEventWithGuard();  // 执行事件
  }
}
这确保了 TcpConnection 至少在整个事件处理过程中都是活的。

✅ 改进 3：使用 EventLoop::QueueOneFunc() 延迟资源释放，保证线程安全
🎯 目的：
避免资源在事件还未完全处理完时就被释放（比如 TcpConnection 析构中关闭 socket/channel，导致 epoll 监听未清理干净）。

保证资源释放与事件处理在同一个线程中执行，解决多线程冲突（如 connectionsMap_ 的并发修改问题）。

🔧 实现机制：
EventLoop 持有一个 std::vector<std::function<void()>> to_do_list_；

提供 QueueOneFunc() 线程安全地加入任务；

在每次 epoll_wait 返回后执行：

cpp
复制
编辑
void EventLoop::Loop() {
    while (true) {
        for (auto* ch : poller_->Poll()) {
            ch->HandleEvent();
        }
        DoToDoList();  // 最后执行清理等延迟任务
    }
}
在 TcpServer::HandleClose() 中通过：

cpp
复制
编辑
main_reactor_->RunOneFunc(std::bind(&TcpServer::HandleCloseInLoop, this, conn));
把清理任务交由主线程（main reactor）处理，避免跨线程访问 connectionsMap_。

✅ 改进 4：通过 eventfd 异步唤醒 epoll_wait，避免任务添加后长时间阻塞
🎯 目的：
解决“epoll_wait 卡住，延迟处理 to_do_list”问题。

实现 “线程唤醒机制”，确保任务立即被处理。

🔧 机制说明：
初始化时创建 eventfd 文件描述符 wakeup_fd_：

cpp
复制
编辑
wakeup_fd_ = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
wakeup_channel_ 绑定这个 fd，并设置为监听读事件。

在 QueueOneFunc() 中，若是跨线程添加任务（非本线程），就：

cpp
复制
编辑
uint64_t one = 1;
::write(wakeup_fd_, &one, sizeof(one));  // 唤醒 epoll_wait
当 epoll_wait() 醒来，执行 wakeup_channel_ 的 read_callback()：

cpp
复制
编辑
void EventLoop::HandleRead() {
    uint64_t one;
    ::read(wakeup_fd_, &one, sizeof(one));  // 清空可读事件
}
✅ 改进 5：统一关闭逻辑放入 HandleCloseInLoop()，消除多线程冲突
🎯 目的：
避免多个线程操作 connectionsMap_，造成数据竞争。

保证关闭操作由主线程统一处理。

🔧 实现：
通过 main_reactor_->RunOneFunc(...) 把 connectionsMap_.erase(...) 放在主线程中执行。

cpp
复制
编辑
void TcpServer::HandleClose(const shared_ptr<TcpConnection>& conn) {
    main_reactor_->RunOneFunc(std::bind(&TcpServer::HandleCloseInLoop, this, conn));
}
🧠 总结：这一系列改动解决了哪些核心问题？
问题	解决方式
悬垂指针 / 早期析构	shared_ptr + tie() + lock() 保证事件期间连接活着
HandleEvent 后清理不及时	QueueOneFunc 将清理延后执行
多线程并发修改 connectionsMap_	统一由 main_reactor 清理连接
epoll_wait 阻塞导致任务延迟执行	eventfd + wakeup_channel_ 异步唤醒
TcpConnection 生命周期难控制	shared_ptr + 事件引用保护 + 延迟清理

整体模块关系图:

                            ┌──────────────┐
                            │ TcpServer    │  负责监听、分发连接
                            └─────┬────────┘
                                  │
                                  ▼
                        ┌──────────────────┐
                        │   Acceptor       │   监听 listen_fd
                        └────────┬─────────┘
                                 │
                                 ▼
                        ┌──────────────────┐
                        │ New Conn(fd)     │
                        │ => TcpConnection │
                        └────────┬─────────┘
                                 │
                                 ▼
                        ┌──────────────────┐
                        │   TcpConnection  │
                        └─────┬────────────┘
                              │
          ┌──────────────────┼───────────────────┐
          ▼                  ▼                   ▼
  ┌──────────────┐   ┌──────────────┐   ┌────────────────────┐
  │   Channel    │   │  Buffer      │   │ shared_ptr 生命周期 │
  └──────┬───────┘   └────┬─────────┘   └──────────┬─────────┘
         │                │                        │
         ▼                ▼                        ▼
    epoll_wait      read/write                 引用计数管理
         │
         ▼
 ┌──────────────┐
 │  EventLoop   │  调度器、注册事件、执行任务队列
 └──────┬───────┘
        ▼
┌────────────────────┐
│ wakeup_fd + do list│ <- queueOneFunc() from other threads
└────────────────────┘

连接生命周期关键状态图:
连接建立阶段
    ↓
TcpServer::handleNewConnection(fd)
    ↓
new TcpConnection(fd)
    ↓
conn->connectionEstablished()
    ↓
channel->tie(shared_from_this())
    ↓
channel->enableRead()
    ↓
开始监听客户端消息

    ↓ （客户端断开或服务端检测到 EOF）
TcpConnection::readNonBlocking()
    ↓
read() == 0 → EOF
    ↓
handleClose()
    ↓
state = Disconnected
loop->deleteChannel()
    ↓
TcpServer::handleClose()
    ↓
mainReactor->runOneFunc(handleCloseInLoop)
    ↓
connection 从 map 中移除
loop->queueOneFunc(connectionDestructor)
    ↓
loop::doToDoList 执行 deleteChannel
    ↓
TcpConnection 销毁
