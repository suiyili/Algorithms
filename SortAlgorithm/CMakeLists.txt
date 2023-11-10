cmake_minimum_required(VERSION 2.26)
project(SortAlgorithm)

include(../base.cmake)

set(SRC heapsort/heap/heap_test.cpp
        heapsort/heapsort_test.cpp
        quicksort/partitioner/partitioner_test.cpp
        quicksort/quicksort_test.cpp
        )
add_executable(SortAlgorithm ${SRC})
target(SortAlgorithm)

