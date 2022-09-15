cmake_minimum_required()

project(BitTree)

include(../base.cmake)

set(SRC node/bit_node/bit_node.cpp
        node/bit_node/bit_node_test.cpp
        bit_tree/bit_tree.cpp
        bit_tree/bit_tree_test.cpp
        node/leaf_node/leaf_node_test.cpp
        node/mock_node/mock_node.cpp
        generic/resource_manager/resource_manager.cpp
        )
add_executable(BitTree ${SRC})
target(BitTree)

