cmake_minimum_required(VERSION 3.10)
project(mywebserver_stage1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

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

set(SOURCES5
        timer/Timer.cpp
        timer/TimerQueue.cpp)

set(SOURCES6
        log/LogStream.cpp
        log/Logging.cpp
        log/AsyncLogging.cpp
        log/LogFile.cpp)


# 可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 添加可执行文件
add_executable(echo_server  
               test/echo_server.cpp
               ${SOURCES1}
               ${SOURCES4}
               ${SOURCES5}
               ${SOURCES6})

# 包含头文件目录
target_include_directories(echo_server PRIVATE tcp)
target_include_directories(echo_server PRIVATE base)
target_include_directories(echo_server PRIVATE http)
target_include_directories(echo_server PRIVATE timer)
target_include_directories(echo_server PRIVATE log)

# 添加依赖库
find_package(Threads REQUIRED)
target_link_libraries(echo_server PRIVATE Threads::Threads)


# 添加可执行文件
add_executable(client  
               test/client.cpp
               ${SOURCES1}
               ${SOURCES2}
               ${SOURCES4}
               ${SOURCES5}
               ${SOURCES6})

# 包含头文件目录
target_include_directories(client PRIVATE tcp)
target_include_directories(client PRIVATE base)
target_include_directories(client PRIVATE timer)
target_include_directories(client PRIVATE log)
target_include_directories(client PRIVATE http)

# 添加依赖库
target_link_libraries(client PRIVATE Threads::Threads)

# 添加可执行文件
add_executable(testServer  
               test/testServer.cpp
               ${SOURCES1}
               ${SOURCES3}
               ${SOURCES4}
               ${SOURCES5}
               ${SOURCES6})

# 包含头文件目录
target_include_directories(testServer PRIVATE tcp)
target_include_directories(testServer PRIVATE base)
target_include_directories(testServer PRIVATE timer)
target_include_directories(testServer PRIVATE log)
target_include_directories(testServer PRIVATE http)

# 添加依赖库
target_link_libraries(testServer PRIVATE Threads::Threads)

# 添加可执行文件
add_executable(http_server  
               test/http_server.cpp
               ${SOURCES1}
               ${SOURCES4}
               ${SOURCES5}
               ${SOURCES6})       
               

# 包含头文件目录
target_include_directories(http_server PRIVATE tcp)
target_include_directories(http_server PRIVATE base)
target_include_directories(http_server PRIVATE http)
target_include_directories(http_server PRIVATE timer)
target_include_directories(http_server PRIVATE log)

# 添加依赖库
target_link_libraries(http_server PRIVATE Threads::Threads)

# 添加可执行文件
add_executable(test_logstream  
               test/test_logstream.cpp
               ${SOURCES1}
               ${SOURCES4}
               ${SOURCES5}
               ${SOURCES6})

# 包含头文件目录
target_include_directories(test_logstream PRIVATE log)
target_include_directories(test_logstream PRIVATE base)
target_include_directories(test_logstream PRIVATE tcp)
target_include_directories(test_logstream PRIVATE http)
target_include_directories(test_logstream PRIVATE timer)

# 添加依赖库
target_link_libraries(test_logstream PRIVATE Threads::Threads)
