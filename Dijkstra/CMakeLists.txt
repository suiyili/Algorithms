cmake_minimum_required()

project(Dijkstra)

include(../base.cmake)

set(SRC generic/item/item.cpp
        generic/priority_queue/priority_queue_test.cpp
        generic/resource_manager/resource_manager.cpp
        shortest_path/shortest_path.cpp
        shortest_path/shortest_path_test.cpp
        )
add_executable(Dijkstra ${SRC})
target(Dijkstra)
