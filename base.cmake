cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH ../../Catch2/Catch)

find_package(Catch2 3.0 REQUIRED)
find_package(Threads REQUIRED)


add_compile_definitions(TEST)

function(target name)
    target_include_directories(${name} PRIVATE ./)
    target_link_libraries(${name} PRIVATE Catch2::Catch2WithMain Threads::Threads)
endfunction()
