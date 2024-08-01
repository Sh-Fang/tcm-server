cmake_minimum_required(VERSION 3.10)

# project name
project(ClientServerApp VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# add executable
add_executable(server ${PROJECT_SOURCE_DIR}/src/server.cpp)
add_executable(client ${PROJECT_SOURCE_DIR}/src/client.cpp)