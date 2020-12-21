cmake_minimum_required(VERSION 3.12)
project(LinearAlgebra)

set(CMAKE_CXX_STANDARD 17)
find_package(Threads)

include_directories(../Catch2)

AUX_SOURCE_DIRECTORY(./ SRC)
add_definitions(-DTEST)
add_executable(LinearAlgebra ${SRC})
target_link_libraries(LinearAlgebra ${CMAKE_THREAD_LIBS_INIT})
