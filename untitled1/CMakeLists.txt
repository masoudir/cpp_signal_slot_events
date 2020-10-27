cmake_minimum_required(VERSION 2.8)

project(untitled1)

set(CMAKE_CXX_FLAGS -pthread)
#set(EVENT_LOG)
add_executable(${PROJECT_NAME} "main.cpp" "lib/Event.cpp" "lib/Signal.cpp")
add_executable(test "test.cpp")
