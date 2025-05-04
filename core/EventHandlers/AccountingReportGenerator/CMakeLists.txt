cmake_minimum_required(VERSION 3.30)
project(yadro)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_COMPILER "/usr/bin/clang++")
add_compile_options(-g -O0)
add_library(accounting_report_generator STATIC
        src/AccountingReportGenerator.cpp
        src/AccountingReport.cpp)
target_include_directories(accounting_report_generator PUBLIC include)
target_link_libraries(accounting_report_generator reporting_system event_listener event_processor accounting monitoring)