cmake_minimum_required()
project(MaximumSubarray)

include(../base.cmake)

set(SRC find_maximum_subarray/find_maximum_subarray_test.cpp
        subarray/subarray_test.cpp
        )
add_executable(MaximumSubarray ${SRC})
target(MaximumSubarray)
