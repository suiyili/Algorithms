#ifdef TEST

#include "leaf_node.hpp"
#include "node/mock_node/mock_node.hpp"
#include <catch2/catch_test_macros.hpp>

namespace tree {
  SCENARIO("leaf node test", "[leaf_node]"){
    GIVEN("a leaf node") {
      auto value = std::make_unique<char>('v');
      leaf_node leaf(value.get());
      node_i& node = leaf;
      CHECK_FALSE(node.any_child());
      WHEN("put a child") {
        auto child = new mock_node();
        auto replaced = node.put_child(side::left, child);
        THEN("it should return the added child") {
          REQUIRE(replaced == child);
        }
        THEN("it has no child") {
          REQUIRE_FALSE(node.any_child());
        }
        THEN("it always gets no child") {
          REQUIRE(node.get_child(side::left) == nullptr);
        }
      }
      WHEN("get value")
      {
        auto v = leaf.get_value();
        THEN("it should get the init value")
        {
          REQUIRE(v == value.get());
        }
      }
    }
  }
}

#endif // TEST
