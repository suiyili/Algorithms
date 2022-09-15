#ifdef TEST

#include <catch2/catch_test_macros.hpp>

#include "trie/trie_node/trie_node_mock/trie_node_mock.hpp"

namespace pattern_match::trie {

SCENARIO("trie node test", "[trie_node]") {
  GIVEN("a char") {
    char c = 'a';
    WHEN("create a trie node") {
      trie_node_mock node(c);
      THEN("its trie node can be converted to the char") {
        REQUIRE((char)node == c);
      }
    }
  }
}

}  // namespace pattern_match::trie

#endif  // TEST
