cmake_minimum_required(VERSION 3.30)
project(yadro)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_compile_options(-g -O0)

add_library(accounting_logger STATIC src/AccountingLogger.cpp)
target_include_directories(accounting_logger PUBLIC include)
target_link_libraries(accounting_logger logging event_listener accounting_report_generator)