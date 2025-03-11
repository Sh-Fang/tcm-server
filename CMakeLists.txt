cmake_minimum_required(VERSION 3.10)
project(TCMServer)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加 include 目录
include_directories(include third_party)

# 添加源文件
add_executable(TCMServer src/main.cpp src/GraphMatch.cpp)

# 链接 pthread 线程库（httplib库需要）
find_package(Threads REQUIRED)
target_link_libraries(TCMServer PRIVATE Threads::Threads)