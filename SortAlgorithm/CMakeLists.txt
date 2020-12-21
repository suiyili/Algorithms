cmake_minimum_required(VERSION 3.12)
project(SortAlgorithm)

set(CMAKE_CXX_STANDARD 17)

include_directories(../Catch2)

AUX_SOURCE_DIRECTORY(./ SortAlgorithm_SRC)

add_executable(SortAlgorithm ${SortAlgorithm_SRC})
