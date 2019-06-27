cmake_minimum_required(VERSION 3.12)
project(MCQ_Correction)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.67.0 COMPONENTS filesystem thread REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
add_executable(MCQ_Correction main.cpp Model/DatabaseManager.cpp Model/DatabaseManager.h Controller/String-Operations/base64.cpp Controller/String-Operations/base64.h Controller/String-Operations/hash.cpp Controller/String-Operations/hash.h Controller/httpHeaders.h Controller/Scan-Analyses/Scanner.cpp Controller/Scan-Analyses/Scanner.h Controller/Scan-Analyses/MainScan.cpp Controller/Scan-Analyses/MainScan.h Controller/DownloadManager.cpp Controller/DownloadManager.h Controller/String-Operations/randomString.cpp Controller/String-Operations/randomString.h Controller/String-Operations/splitString.cpp Controller/String-Operations/splitString.h Controller/RequestManagement.cpp Controller/RequestManagement.h)

include_directories(${Boost_INCLUDE_DIR})
include_directories(/usr/include/soci)
include_directories(/usr/include/soci/mysql)
include_directories(/usr/include/mysql)

target_link_libraries(MCQ_Correction ${Boost_LIBRARIES} pthread ${OPENSSL_LIBRARIES})
target_link_libraries(MCQ_Correction soci_core soci_mysql)
target_link_libraries(MCQ_Correction config++)
target_link_libraries(MCQ_Correction Qt5::Widgets)
target_link_libraries(MCQ_Correction Qt5::Network)