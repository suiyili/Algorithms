#ifdef TEST

#include "leaf_node.hpp"

#include <catch2/catch_test_macros.hpp>
#include <memory>

namespace pattern_match::trie {

SCENARIO("leaf node test", "[leaf_node]") {
  GIVEN("a leaf node") {
    leaf_node node('s');
    WHEN("check if it is end") {
      THEN("it is end") { REQUIRE(node.is_end()); }
    }
    WHEN("check if it is leaf") {
      THEN("it is leaf") { REQUIRE(node.is_leaf()); }
    }
    WHEN("count the number of children") {
      THEN("it should return 1") { REQUIRE(node.count_children() == 1U); }
    }
    WHEN("get next child") {
      auto next = node.next_child();
      THEN("it should return null") { REQUIRE(next == nullptr); }
    }
    AND_GIVEN("a child") {
      auto child = 'c';
      WHEN("add a child") {
        auto inserted = node.insert(std::make_unique<leaf_node>(child));
        THEN("inserted is null") { REQUIRE_FALSE(inserted); }
        AND_WHEN("try to find") {
          auto found = node.find(child);
          THEN("it can't be found") { REQUIRE_FALSE(found); }
        }
      }
    }
  }
}

}  // namespace pattern_match::trie

#endif  // TEST
