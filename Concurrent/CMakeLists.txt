cmake_minimum_required()
project(Concurrent)

include(../base.cmake)

set(SRC queue/atomic_item/atomic_item.cpp
        queue/atomic_item/atomic_item_test.cpp
        queue/queue_test.cpp
        shared_lock/shared_lock.cpp
        shared_lock/shared_lock_test.cpp
        spin_lock/spin_lock.cpp
        spin_lock/spin_lock_test.cpp
        )
add_executable(Concurrent ${SRC})
target(Concurrent)
