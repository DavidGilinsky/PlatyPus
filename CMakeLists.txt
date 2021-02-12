cmake_minimum_required(VERSION 3.9)
project(PlatyPus)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp main.cpp main.h sig_handler.cpp sig_handler.h tcp_listener.cpp tcp_listener.h node_manager.cpp node_manager.h data_integrity.cpp data_integrity.h locks.h locks.cpp sensors/1-Wire/DS18B20-Temperature-GPIO-4.cpp sensors/1-Wire/DS18B20-Temperature-GPIO-4.h sensor_data.h udp_listener.cpp udp_listener.h udp_broadcast.cpp udp_broadcast.h tcp_connection_manager.cpp tcp_connection_manager.h)
add_executable(PlatyPus ${SOURCE_FILES})

target_link_libraries (${PROJECT_NAME} pthread)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpu=neon -I/usr/arm-linux-gnueabi/include")
