cmake_minimum_required(VERSION 3.12)
project(MCQ_Correction)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Boost 1.67.0 COMPONENTS filesystem thread REQUIRED)
find_package(OpenSSL REQUIRED)
add_executable(MCQ_Correction main.cpp)

include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(MCQ_Correction ${Boost_LIBRARIES} pthread ${OPENSSL_LIBRARIES})