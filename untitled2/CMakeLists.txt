cmake_minimum_required(VERSION 2.8)

project(test_event)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
#set(EVENT_LOG)
add_executable(${PROJECT_NAME} main.cpp)
