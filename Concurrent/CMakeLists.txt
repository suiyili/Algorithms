cmake_minimum_required(VERSION 3.12)
project(Concurrent)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads)
include_directories(../Catch2)

AUX_SOURCE_DIRECTORY(./ Concurrent_SRC)

add_executable(Concurrent ${Concurrent_SRC})
target_link_libraries(Concurrent pthread)