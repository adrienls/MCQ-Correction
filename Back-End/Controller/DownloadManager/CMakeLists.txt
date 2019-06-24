cmake_minimum_required(VERSION 3.14)
project(QtDownloader2)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

add_executable(QtDownloader2 main.cpp DownloadManager.cpp DownloadManager.h)

target_link_libraries(QtDownloader2 Qt5::Widgets Qt5::Network config++)