cmake_minimum_required(VERSION 3.26)

project(BalancedBinaryTree)

include(../base.cmake)

set(SRC
        algo/insert_node/insert_node_test.cpp
        rb_node/rb_node_test.cpp
        rb_tree/rb_tree_test.cpp
        generic/resource_manager/resource_manager.cpp
        algo/regulate_red/regulate_red_test.cpp
        algo/regulate_black/regulate_black_test.cpp
        algo/remove_node/remove_node_test.cpp
)

add_executable(BalancedBinaryTree ${SRC})
target(BalancedBinaryTree)




