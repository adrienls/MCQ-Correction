cmake_minimum_required(VERSION 3.7.2)
project(scan_prototype2)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)

find_package(Qt5Widgets CONFIG REQUIRED)
add_executable(scan_prototype2 main.cpp Scanner.cpp Scanner.h debug.h)
target_link_libraries(scan_prototype2 Qt5::Widgets)