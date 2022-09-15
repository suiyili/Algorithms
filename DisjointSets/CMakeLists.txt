cmake_minimum_required()
project(DisjointSets)

include(../base.cmake)

set(RNN_SRC
        main.cpp
        )
add_executable(DisjointSets ${RNN_SRC})
target(DisjointSets)