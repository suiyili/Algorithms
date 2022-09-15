#ifdef TEST

#include <catch2/catch_test_macros.hpp>

#include "trie/trie_node/stem_node/end_node/end_node.hpp"
#include "trie/trie_node/stem_node/middle_node/middle_node.hpp"
#include "trie/trie_node/trie_node_mock/trie_node_mock.hpp"

namespace pattern_match::trie {

SCENARIO("stem node test", "[stem_node]") {
  GIVEN("an end node") {
    end_node end('s');
    WHEN("check if it is end") {
      THEN("it is end") { REQUIRE(end.is_end()); }
    }
    WHEN("check if it is leaf") {
      THEN("it is not leaf") { REQUIRE_FALSE(end.is_leaf()); }
    }
    WHEN("count the number of children") {
      THEN("it should return one") { REQUIRE(end.count_children() == 1U); }
    }
    AND_GIVEN("a child") {
      char c = 'c';
      WHEN("add a child") {
        auto inserted = end.insert(std::make_unique<end_node>(c));
        THEN("inserted is the child") {
          REQUIRE(inserted);
          REQUIRE(inserted->is_end());
          REQUIRE((char)(*inserted) == c);
          AND_THEN("count children is two") {
            REQUIRE(end.count_children() == 2U);
          }
        }
        AND_WHEN("get next child"){
          auto next = end.next_child();
          THEN("it should get the inserted one"){
            REQUIRE(next == inserted);
            AND_WHEN("get next again"){
              auto second_next = end.next_child();
              THEN("it should get null/end"){
                REQUIRE(second_next == nullptr);
              }
              AND_WHEN("get next after end"){
                auto round_next = end.next_child();
                THEN("it should get back the beginning"){
                  REQUIRE(round_next == inserted);
                }
              }
            }
          }
        }
        AND_WHEN("add another same child") {
          auto another = end.insert(std::make_unique<middle_node>(c));
          THEN("new inserted relpaces the old child") {
            REQUIRE(another);
            REQUIRE_FALSE(another->is_end());
            REQUIRE((char)(*another) == c);
          }
        }
        AND_WHEN("try to find") {
          auto found = end.find(c);
          THEN("it can be found") { REQUIRE(found); }
        }
      }
    }
  }

  GIVEN("an middle node") {
    middle_node middle('s');
    WHEN("check if it is end") {
      THEN("it is not end") { REQUIRE_FALSE(middle.is_end()); }
    }
    WHEN("check if it is leaf") {
      THEN("it is not leaf") { REQUIRE_FALSE(middle.is_leaf()); }
    }
    WHEN("count the number of children") {
      THEN("it should return 0") { REQUIRE(middle.count_children() == 0U); }
    }
    AND_GIVEN("a child") {
      char c = 'c';
      WHEN("add a child") {
        middle.insert(std::make_unique<end_node>(c));
        THEN("count children is one") {
          REQUIRE(middle.count_children() == 1U);
        }
      }
    }
  }
}

}  // namespace pattern_match::trie

#endif  // TEST
