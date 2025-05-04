cmake_minimum_required(VERSION 3.30)
project(yadro)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_compile_options(-g -O0)
add_library(event_report_generator STATIC src/EventReportGenerator.cpp src/EventReport.cpp)
target_include_directories(event_report_generator PUBLIC include ../../../utilities)
target_link_libraries(event_report_generator reporting_system event_processor event_listener logging)