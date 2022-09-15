cmake_minimum_required()
project(PatternMatch)

include(../base.cmake)

set(SRC trie/trie_node/stem_node/end_node/end_node.cpp
        kmp/pattern/kmp_pattern.cpp
        kmp/pattern/kmp_pattern_test.cpp
        kmp/kmp_search.cpp
        kmp/kmp_test.cpp
        trie/trie_node/leaf_node/leaf_node.cpp
        trie/trie_node/leaf_node/leaf_node_test.cpp
        trie/trie_node/stem_node/middle_node/middle_node.cpp
        generic/resource_manager/resource_manager.cpp
        trie/trie_node/stem_node/stem_node.cpp
        trie/trie_node/stem_node/stem_node_test.cpp
        trie/suffix_trie.cpp
        trie/suffix_trie_test.cpp
        trie/trie_node/trie_node.cpp
        trie/trie_node/trie_node_mock/trie_node_mock.cpp
        trie/trie_node/trie_node_test.cpp
        )
add_executable(PatternMatch ${SRC})
target(PatternMatch)
