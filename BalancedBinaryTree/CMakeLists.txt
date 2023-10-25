cmake_minimum_required(VERSION 3.26)

project(BalancedBinaryTree)

include(../base.cmake)

set(SRC algorithm/consecutive_red_regulator/consecutive_red_regulator_test.cpp
        algorithm/dual_black_regulator/dual_black_regulator_test.cpp
        algorithm/node_inserter/node_inserter_test.cpp
        algorithm/node_remover/node_remover_test.cpp
        rb_node/rb_node_test.cpp
        rb_tree/rb_tree_test.cpp
        generic/resource_manager/resource_manager.cpp
        )

add_executable(BalancedBinaryTree ${SRC})
target(BalancedBinaryTree)




