cmake_minimum_required(VERSION 3.30)
project(yadro)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_compile_options(-g -O0)
add_library(monitoring STATIC
        src/GamingStationMonitor.cpp
        src/FlatStationMonitoringSystem.cpp
        src/SimpleClientMonitoringSystem.cpp)
target_include_directories(monitoring PUBLIC include ../../utilities)