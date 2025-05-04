cmake_minimum_required(VERSION 3.30)
project(yadro)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_compile_options(-g -O0)

add_library(orchestrator STATIC src/Orchestrator.cpp)
target_include_directories(orchestrator PUBLIC include)
target_link_libraries(orchestrator
                        club_state
                        monitoring
                        logging
                        accounting
                        client_queue_manager
                        accountant
                        accounting_logger
                        event_logger)