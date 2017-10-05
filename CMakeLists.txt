cmake_minimum_required(VERSION 3.9)
project(PlatyPus)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp main.cpp main.h sig_handler.cpp sig_handler.h tcp_listener.cpp tcp_listener.h)
add_executable(PlatyPus ${SOURCE_FILES})

target_link_libraries (${PROJECT_NAME} pthread)

