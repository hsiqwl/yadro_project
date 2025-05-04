cmake_minimum_required(VERSION 3.30)
project(yadro)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_compile_options(-g -O0)
add_library(event_listener INTERFACE)
target_include_directories(event_listener INTERFACE include)
target_link_libraries(event_listener INTERFACE events)