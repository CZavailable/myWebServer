# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cz/MyProject/mywebserver/stage6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cz/MyProject/mywebserver/stage6/build

# Include any dependencies generated for this target.
include CMakeFiles/testHttpContext.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testHttpContext.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testHttpContext.dir/flags.make

CMakeFiles/testHttpContext.dir/test/testHttpContext.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/test/testHttpContext.cpp.o: ../test/testHttpContext.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testHttpContext.dir/test/testHttpContext.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/test/testHttpContext.cpp.o -c /home/cz/MyProject/mywebserver/stage6/test/testHttpContext.cpp

CMakeFiles/testHttpContext.dir/test/testHttpContext.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/test/testHttpContext.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/test/testHttpContext.cpp > CMakeFiles/testHttpContext.dir/test/testHttpContext.cpp.i

CMakeFiles/testHttpContext.dir/test/testHttpContext.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/test/testHttpContext.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/test/testHttpContext.cpp -o CMakeFiles/testHttpContext.dir/test/testHttpContext.cpp.s

CMakeFiles/testHttpContext.dir/tcp/Acceptor.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/tcp/Acceptor.cpp.o: ../tcp/Acceptor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testHttpContext.dir/tcp/Acceptor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/tcp/Acceptor.cpp.o -c /home/cz/MyProject/mywebserver/stage6/tcp/Acceptor.cpp

CMakeFiles/testHttpContext.dir/tcp/Acceptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/tcp/Acceptor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/tcp/Acceptor.cpp > CMakeFiles/testHttpContext.dir/tcp/Acceptor.cpp.i

CMakeFiles/testHttpContext.dir/tcp/Acceptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/tcp/Acceptor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/tcp/Acceptor.cpp -o CMakeFiles/testHttpContext.dir/tcp/Acceptor.cpp.s

CMakeFiles/testHttpContext.dir/tcp/Buffer.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/tcp/Buffer.cpp.o: ../tcp/Buffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/testHttpContext.dir/tcp/Buffer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/tcp/Buffer.cpp.o -c /home/cz/MyProject/mywebserver/stage6/tcp/Buffer.cpp

CMakeFiles/testHttpContext.dir/tcp/Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/tcp/Buffer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/tcp/Buffer.cpp > CMakeFiles/testHttpContext.dir/tcp/Buffer.cpp.i

CMakeFiles/testHttpContext.dir/tcp/Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/tcp/Buffer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/tcp/Buffer.cpp -o CMakeFiles/testHttpContext.dir/tcp/Buffer.cpp.s

CMakeFiles/testHttpContext.dir/tcp/Channel.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/tcp/Channel.cpp.o: ../tcp/Channel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/testHttpContext.dir/tcp/Channel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/tcp/Channel.cpp.o -c /home/cz/MyProject/mywebserver/stage6/tcp/Channel.cpp

CMakeFiles/testHttpContext.dir/tcp/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/tcp/Channel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/tcp/Channel.cpp > CMakeFiles/testHttpContext.dir/tcp/Channel.cpp.i

CMakeFiles/testHttpContext.dir/tcp/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/tcp/Channel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/tcp/Channel.cpp -o CMakeFiles/testHttpContext.dir/tcp/Channel.cpp.s

CMakeFiles/testHttpContext.dir/tcp/TcpConnection.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/tcp/TcpConnection.cpp.o: ../tcp/TcpConnection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/testHttpContext.dir/tcp/TcpConnection.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/tcp/TcpConnection.cpp.o -c /home/cz/MyProject/mywebserver/stage6/tcp/TcpConnection.cpp

CMakeFiles/testHttpContext.dir/tcp/TcpConnection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/tcp/TcpConnection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/tcp/TcpConnection.cpp > CMakeFiles/testHttpContext.dir/tcp/TcpConnection.cpp.i

CMakeFiles/testHttpContext.dir/tcp/TcpConnection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/tcp/TcpConnection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/tcp/TcpConnection.cpp -o CMakeFiles/testHttpContext.dir/tcp/TcpConnection.cpp.s

CMakeFiles/testHttpContext.dir/tcp/Epoll.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/tcp/Epoll.cpp.o: ../tcp/Epoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/testHttpContext.dir/tcp/Epoll.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/tcp/Epoll.cpp.o -c /home/cz/MyProject/mywebserver/stage6/tcp/Epoll.cpp

CMakeFiles/testHttpContext.dir/tcp/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/tcp/Epoll.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/tcp/Epoll.cpp > CMakeFiles/testHttpContext.dir/tcp/Epoll.cpp.i

CMakeFiles/testHttpContext.dir/tcp/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/tcp/Epoll.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/tcp/Epoll.cpp -o CMakeFiles/testHttpContext.dir/tcp/Epoll.cpp.s

CMakeFiles/testHttpContext.dir/tcp/EventLoop.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/tcp/EventLoop.cpp.o: ../tcp/EventLoop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/testHttpContext.dir/tcp/EventLoop.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/tcp/EventLoop.cpp.o -c /home/cz/MyProject/mywebserver/stage6/tcp/EventLoop.cpp

CMakeFiles/testHttpContext.dir/tcp/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/tcp/EventLoop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/tcp/EventLoop.cpp > CMakeFiles/testHttpContext.dir/tcp/EventLoop.cpp.i

CMakeFiles/testHttpContext.dir/tcp/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/tcp/EventLoop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/tcp/EventLoop.cpp -o CMakeFiles/testHttpContext.dir/tcp/EventLoop.cpp.s

CMakeFiles/testHttpContext.dir/tcp/EventLoopThread.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/tcp/EventLoopThread.cpp.o: ../tcp/EventLoopThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/testHttpContext.dir/tcp/EventLoopThread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/tcp/EventLoopThread.cpp.o -c /home/cz/MyProject/mywebserver/stage6/tcp/EventLoopThread.cpp

CMakeFiles/testHttpContext.dir/tcp/EventLoopThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/tcp/EventLoopThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/tcp/EventLoopThread.cpp > CMakeFiles/testHttpContext.dir/tcp/EventLoopThread.cpp.i

CMakeFiles/testHttpContext.dir/tcp/EventLoopThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/tcp/EventLoopThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/tcp/EventLoopThread.cpp -o CMakeFiles/testHttpContext.dir/tcp/EventLoopThread.cpp.s

CMakeFiles/testHttpContext.dir/tcp/EventLoopThreadPool.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/tcp/EventLoopThreadPool.cpp.o: ../tcp/EventLoopThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/testHttpContext.dir/tcp/EventLoopThreadPool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/tcp/EventLoopThreadPool.cpp.o -c /home/cz/MyProject/mywebserver/stage6/tcp/EventLoopThreadPool.cpp

CMakeFiles/testHttpContext.dir/tcp/EventLoopThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/tcp/EventLoopThreadPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/tcp/EventLoopThreadPool.cpp > CMakeFiles/testHttpContext.dir/tcp/EventLoopThreadPool.cpp.i

CMakeFiles/testHttpContext.dir/tcp/EventLoopThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/tcp/EventLoopThreadPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/tcp/EventLoopThreadPool.cpp -o CMakeFiles/testHttpContext.dir/tcp/EventLoopThreadPool.cpp.s

CMakeFiles/testHttpContext.dir/tcp/TcpServer.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/tcp/TcpServer.cpp.o: ../tcp/TcpServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/testHttpContext.dir/tcp/TcpServer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/tcp/TcpServer.cpp.o -c /home/cz/MyProject/mywebserver/stage6/tcp/TcpServer.cpp

CMakeFiles/testHttpContext.dir/tcp/TcpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/tcp/TcpServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/tcp/TcpServer.cpp > CMakeFiles/testHttpContext.dir/tcp/TcpServer.cpp.i

CMakeFiles/testHttpContext.dir/tcp/TcpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/tcp/TcpServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/tcp/TcpServer.cpp -o CMakeFiles/testHttpContext.dir/tcp/TcpServer.cpp.s

CMakeFiles/testHttpContext.dir/base/CurrentThread.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/base/CurrentThread.cpp.o: ../base/CurrentThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/testHttpContext.dir/base/CurrentThread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/base/CurrentThread.cpp.o -c /home/cz/MyProject/mywebserver/stage6/base/CurrentThread.cpp

CMakeFiles/testHttpContext.dir/base/CurrentThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/base/CurrentThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/base/CurrentThread.cpp > CMakeFiles/testHttpContext.dir/base/CurrentThread.cpp.i

CMakeFiles/testHttpContext.dir/base/CurrentThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/base/CurrentThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/base/CurrentThread.cpp -o CMakeFiles/testHttpContext.dir/base/CurrentThread.cpp.s

CMakeFiles/testHttpContext.dir/http/HttpContext.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/http/HttpContext.cpp.o: ../http/HttpContext.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/testHttpContext.dir/http/HttpContext.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/http/HttpContext.cpp.o -c /home/cz/MyProject/mywebserver/stage6/http/HttpContext.cpp

CMakeFiles/testHttpContext.dir/http/HttpContext.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/http/HttpContext.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/http/HttpContext.cpp > CMakeFiles/testHttpContext.dir/http/HttpContext.cpp.i

CMakeFiles/testHttpContext.dir/http/HttpContext.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/http/HttpContext.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/http/HttpContext.cpp -o CMakeFiles/testHttpContext.dir/http/HttpContext.cpp.s

CMakeFiles/testHttpContext.dir/http/HttpRequest.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/http/HttpRequest.cpp.o: ../http/HttpRequest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/testHttpContext.dir/http/HttpRequest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/http/HttpRequest.cpp.o -c /home/cz/MyProject/mywebserver/stage6/http/HttpRequest.cpp

CMakeFiles/testHttpContext.dir/http/HttpRequest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/http/HttpRequest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/http/HttpRequest.cpp > CMakeFiles/testHttpContext.dir/http/HttpRequest.cpp.i

CMakeFiles/testHttpContext.dir/http/HttpRequest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/http/HttpRequest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/http/HttpRequest.cpp -o CMakeFiles/testHttpContext.dir/http/HttpRequest.cpp.s

CMakeFiles/testHttpContext.dir/http/HttpResponse.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/http/HttpResponse.cpp.o: ../http/HttpResponse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/testHttpContext.dir/http/HttpResponse.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/http/HttpResponse.cpp.o -c /home/cz/MyProject/mywebserver/stage6/http/HttpResponse.cpp

CMakeFiles/testHttpContext.dir/http/HttpResponse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/http/HttpResponse.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/http/HttpResponse.cpp > CMakeFiles/testHttpContext.dir/http/HttpResponse.cpp.i

CMakeFiles/testHttpContext.dir/http/HttpResponse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/http/HttpResponse.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/http/HttpResponse.cpp -o CMakeFiles/testHttpContext.dir/http/HttpResponse.cpp.s

CMakeFiles/testHttpContext.dir/http/HttpServer.cpp.o: CMakeFiles/testHttpContext.dir/flags.make
CMakeFiles/testHttpContext.dir/http/HttpServer.cpp.o: ../http/HttpServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/testHttpContext.dir/http/HttpServer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testHttpContext.dir/http/HttpServer.cpp.o -c /home/cz/MyProject/mywebserver/stage6/http/HttpServer.cpp

CMakeFiles/testHttpContext.dir/http/HttpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testHttpContext.dir/http/HttpServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cz/MyProject/mywebserver/stage6/http/HttpServer.cpp > CMakeFiles/testHttpContext.dir/http/HttpServer.cpp.i

CMakeFiles/testHttpContext.dir/http/HttpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testHttpContext.dir/http/HttpServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cz/MyProject/mywebserver/stage6/http/HttpServer.cpp -o CMakeFiles/testHttpContext.dir/http/HttpServer.cpp.s

# Object files for target testHttpContext
testHttpContext_OBJECTS = \
"CMakeFiles/testHttpContext.dir/test/testHttpContext.cpp.o" \
"CMakeFiles/testHttpContext.dir/tcp/Acceptor.cpp.o" \
"CMakeFiles/testHttpContext.dir/tcp/Buffer.cpp.o" \
"CMakeFiles/testHttpContext.dir/tcp/Channel.cpp.o" \
"CMakeFiles/testHttpContext.dir/tcp/TcpConnection.cpp.o" \
"CMakeFiles/testHttpContext.dir/tcp/Epoll.cpp.o" \
"CMakeFiles/testHttpContext.dir/tcp/EventLoop.cpp.o" \
"CMakeFiles/testHttpContext.dir/tcp/EventLoopThread.cpp.o" \
"CMakeFiles/testHttpContext.dir/tcp/EventLoopThreadPool.cpp.o" \
"CMakeFiles/testHttpContext.dir/tcp/TcpServer.cpp.o" \
"CMakeFiles/testHttpContext.dir/base/CurrentThread.cpp.o" \
"CMakeFiles/testHttpContext.dir/http/HttpContext.cpp.o" \
"CMakeFiles/testHttpContext.dir/http/HttpRequest.cpp.o" \
"CMakeFiles/testHttpContext.dir/http/HttpResponse.cpp.o" \
"CMakeFiles/testHttpContext.dir/http/HttpServer.cpp.o"

# External object files for target testHttpContext
testHttpContext_EXTERNAL_OBJECTS =

../bin/testHttpContext: CMakeFiles/testHttpContext.dir/test/testHttpContext.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/tcp/Acceptor.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/tcp/Buffer.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/tcp/Channel.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/tcp/TcpConnection.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/tcp/Epoll.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/tcp/EventLoop.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/tcp/EventLoopThread.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/tcp/EventLoopThreadPool.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/tcp/TcpServer.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/base/CurrentThread.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/http/HttpContext.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/http/HttpRequest.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/http/HttpResponse.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/http/HttpServer.cpp.o
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/build.make
../bin/testHttpContext: CMakeFiles/testHttpContext.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cz/MyProject/mywebserver/stage6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable ../bin/testHttpContext"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testHttpContext.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testHttpContext.dir/build: ../bin/testHttpContext

.PHONY : CMakeFiles/testHttpContext.dir/build

CMakeFiles/testHttpContext.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testHttpContext.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testHttpContext.dir/clean

CMakeFiles/testHttpContext.dir/depend:
	cd /home/cz/MyProject/mywebserver/stage6/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cz/MyProject/mywebserver/stage6 /home/cz/MyProject/mywebserver/stage6 /home/cz/MyProject/mywebserver/stage6/build /home/cz/MyProject/mywebserver/stage6/build /home/cz/MyProject/mywebserver/stage6/build/CMakeFiles/testHttpContext.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testHttpContext.dir/depend

