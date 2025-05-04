cmake_minimum_required(VERSION 3.30)
project(yadro)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_compile_options(-g -O0)
add_library(event_logger STATIC src/EventLogger.cpp)
target_include_directories(event_logger PUBLIC include)
target_link_libraries(event_logger logging event_listener event_report_generator)