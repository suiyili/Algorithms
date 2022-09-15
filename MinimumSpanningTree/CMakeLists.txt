cmake_minimum_required()
project(MinimumSpanningTree)

include(../base.cmake)

set(SRC generic/connect/connect.cpp
        generic/connect/connect_test.cpp
        minimum_spanning_tree/minimum_spanning_tree.cpp
        minimum_spanning_tree/minimum_spanning_tree_test.cpp
        generic/resource_manager/resource_manager.cpp
        tree_retriever/tree_retriever.cpp
        tree_retriever/tree_retriever_test.cpp
        )
add_executable(MinimumSpanningTree ${SRC})
target(MinimumSpanningTree)