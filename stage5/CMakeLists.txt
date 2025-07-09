cmake_minimum_required(VERSION 3.10)
project(mywebserver_stage1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置源代码目录
set(SOURCES1 
        src/Acceptor.cpp
        src/Buffer.cpp
        src/Channel.cpp
        src/TcpConnection.cpp
        src/Epoll.cpp
        src/EventLoop.cpp
        src/EventLoopThread.cpp
        src/EventLoopThreadPool.cpp
        src/TcpServer.cpp
        src/CurrentThread.cpp)

set(SOURCES2   
        src/Buffer.cpp)

set(SOURCES3   
        src/Buffer.cpp
        src/ThreadPool.cpp)


# 可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 添加可执行文件
add_executable(server  
               test/server.cpp
               ${SOURCES1})

# 包含头文件目录
target_include_directories(server PRIVATE include)

# 添加依赖库
find_package(Threads REQUIRED)
target_link_libraries(server PRIVATE Threads::Threads)


# 添加可执行文件
add_executable(client  
               test/client.cpp
               ${SOURCES2})

# 包含头文件目录
target_include_directories(client PRIVATE include)

# 添加可执行文件
add_executable(testServer  
               test/testServer.cpp
               ${SOURCES3})

# 包含头文件目录
target_include_directories(testServer PRIVATE include)

# 添加依赖库
target_link_libraries(testServer PRIVATE Threads::Threads)

