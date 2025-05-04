cmake_minimum_required(VERSION 3.30)
project(yadro)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_compile_options(-g -O0)
add_library(client_queue_manager STATIC src/ClientQueueManager.cpp)
target_include_directories(client_queue_manager PUBLIC include)
target_link_libraries(client_queue_manager event_listener event_processor club_state monitoring)