cmake_minimum_required(VERSION 3.30)
project(yadro)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_compile_options(-g -O0)
add_library(event_processor INTERFACE)
target_include_directories(event_processor INTERFACE include)
target_link_libraries(event_processor INTERFACE events)