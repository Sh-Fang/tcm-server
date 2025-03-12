cmake_minimum_required(VERSION 3.10)
project(TCMServer)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加 include 目录
include_directories(include third_party)

# 添加源文件
add_executable(TCMServer
        src/jsonHandle.cpp
        src/tc_arg.cpp
        src/tc_g_index.cpp
        src/tc_global_index.cpp
        src/tc_io.cpp
        src/tc_match_order.cpp
        src/tc_misc.cpp
        src/tc_offline_index.cpp
        src/tc_search.cpp
        src/tc_match.cpp
        src/httpHandle.cpp
        src/main.cpp
        )

# 链接 pthread 线程库（httplib库需要）
find_package(Threads REQUIRED)
target_link_libraries(TCMServer PRIVATE Threads::Threads)