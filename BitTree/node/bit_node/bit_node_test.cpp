#ifdef TEST

#include "bit_node.hpp"
#include "node/mock_node/mock_node.hpp"
#include <catch2/catch_test_macros.hpp>

namespace tree {
SCENARIO("bit node test", "[bit_node]") {
  GIVEN("a bit node") {
    bit_node bnode;
    node_i &node = bnode;
    WHEN("put a child in it") {
      auto mock_child = new mock_node();
      auto c = node.put_child(side::left, mock_child);
      THEN("it should have children") {
        REQUIRE(node.any_child());
      }
      AND_WHEN("get a given side child") {
        auto child = node.get_child(side::left);
        THEN("it should be the designated one") {
          REQUIRE(child == mock_child);
        }
        auto right_child = node.get_child(side::right);
        THEN("it should not get non-added child") {
          REQUIRE(right_child == nullptr);
        }
      }
      AND_WHEN("add another child to replace existing child") {
        auto prev = node.put_child(side::left, nullptr);        
        THEN("it should return previous child") {
          REQUIRE(prev == mock_child);
        }
      }
    }
  }
}
} // namespace tree

#endif // TEST
