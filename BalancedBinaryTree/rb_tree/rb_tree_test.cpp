#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include "../algorithm/node_inserter/node_inserter.hpp"
#include "../algorithm/node_remover/node_remover.hpp"
#include "rb_tree.hpp"

using namespace btree::node;
using namespace btree::algorithm;

namespace btree {

using item_inserter_t = node_inserter<int>;

SCENARIO("red black tree test", "[rb_tree]") {
  GIVEN("a number of items inserted") {
    const int key_exists = 9, non_existing_key = 32;

    rb_tree<int> tree;
    std::vector<item_inserter_t> inserters;
    inserters.reserve(10);
    inserters.emplace_back(-2);
    inserters.emplace_back(key_exists);
    inserters.emplace_back(8);
    inserters.emplace_back(15);
    inserters.emplace_back(6);
    inserters.emplace_back(33);

    for (auto &i : inserters)
      tree.accept(i);

    WHEN("search the given key") {
      auto found = tree.contains(key_exists);
      THEN("it should be found") { REQUIRE(found); }
    }

    AND_WHEN("search a non-exsiting key") {
      THEN("it should return false") {
        REQUIRE_FALSE(tree.contains(non_existing_key));
      }
    }

    AND_WHEN("insert an existing key") {
      THEN("it will throw") {
        item_inserter_t insert_existing(key_exists);
        REQUIRE_THROWS_AS(tree.accept(insert_existing), item_already_exists);
      }
    }

    AND_WHEN("remove an existing key") {
      const int to_remove(key_exists);
      node_remover remove_existing(to_remove);
      
      tree.accept(remove_existing);

      THEN("the key should be removed from the tree") {
        REQUIRE_FALSE(tree.contains(key_exists));
      }
    }

    AND_WHEN("remove non-existing key") {
      const int to_remove(non_existing_key);

      THEN("it will throw") {
        node_remover remove_existing(to_remove);
        REQUIRE_THROWS_AS(tree.accept(remove_existing), item_not_exists);
      }
    }
  }
}
} // namespace btree

#endif // TEST