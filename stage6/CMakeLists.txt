cmake_minimum_required(VERSION 3.10)
project(mywebserver_stage1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置源代码目录
set(SOURCES1 
        tcp/Acceptor.cpp
        tcp/Buffer.cpp
        tcp/Channel.cpp
        tcp/TcpConnection.cpp
        tcp/Epoll.cpp
        tcp/EventLoop.cpp
        tcp/EventLoopThread.cpp
        tcp/EventLoopThreadPool.cpp
        tcp/TcpServer.cpp
        base/CurrentThread.cpp)

set(SOURCES2   
        tcp/Buffer.cpp)

set(SOURCES3   
        tcp/Buffer.cpp
        base/ThreadPool.cpp)

set(SOURCES4   
        http/HttpContext.cpp
        http/HttpRequest.cpp
        http/HttpResponse.cpp
        http/HttpServer.cpp)


# 可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 添加可执行文件
add_executable(echo_server  
               test/echo_server.cpp
               ${SOURCES1}
               ${SOURCES4})

# 包含头文件目录
target_include_directories(echo_server PRIVATE tcp)
target_include_directories(echo_server PRIVATE base)
target_include_directories(echo_server PRIVATE http)

# 添加依赖库
find_package(Threads REQUIRED)
target_link_libraries(echo_server PRIVATE Threads::Threads)


# 添加可执行文件
add_executable(client  
               test/client.cpp
               ${SOURCES2})

# 包含头文件目录
target_include_directories(client PRIVATE tcp)
target_include_directories(client PRIVATE base)

# 添加可执行文件
add_executable(testServer  
               test/testServer.cpp
               ${SOURCES3})

# 包含头文件目录
target_include_directories(testServer PRIVATE tcp)
target_include_directories(testServer PRIVATE base)

# 添加依赖库
target_link_libraries(testServer PRIVATE Threads::Threads)

# 添加可执行文件
add_executable(http_server  
               test/http_server.cpp
               ${SOURCES1}
               ${SOURCES4})       
               

# 包含头文件目录
target_include_directories(http_server PRIVATE tcp)
target_include_directories(http_server PRIVATE base)
target_include_directories(http_server PRIVATE http)

# 添加依赖库
target_link_libraries(http_server PRIVATE Threads::Threads)


# 添加可执行文件
add_executable(testHttpContext  
               test/testHttpContext.cpp
               ${SOURCES1}
               ${SOURCES4})       
               

# 包含头文件目录
target_include_directories(testHttpContext PRIVATE tcp)
target_include_directories(testHttpContext PRIVATE base)
target_include_directories(testHttpContext PRIVATE http)

# 添加依赖库
target_link_libraries(testHttpContext PRIVATE Threads::Threads)

