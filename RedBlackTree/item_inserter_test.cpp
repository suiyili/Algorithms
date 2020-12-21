#ifdef TEST

#include <catch2/catch.hpp>
#include "item_already_exists.hpp"
#include "item_inserter.hpp"

namespace bbtree::algorithm {

const int existing_key = 1;
static rb_item<int> *set_up_tree();

SCENARIO("item inserter test", "[item_inserter]") {
  GIVEN("a rb-tree with some items setup") {
    auto tree_top = set_up_tree();
    item_handle root(tree_top);

    WHEN("inserting a new item") {
      const int key_to_insert = 4;
      item_inserter inserter(std::make_unique<int>(key_to_insert));
      tree_visitor_i<int> &visitor = inserter;
      visitor.visit(root);

      THEN("it should follow red black tree insert rule") {
        REQUIRE(root->get_key() == 7);
        REQUIRE(root->color() == 1U);

        auto left = root->left;
        REQUIRE(left->get_key() == 2);
        REQUIRE(left->color() == 0U);

        auto ll = left->left;
        REQUIRE(ll->get_key() == existing_key);
        REQUIRE(ll->color() == 1U);

        auto lr = left->right;
        REQUIRE(lr->get_key() == 5);
        REQUIRE(lr->color() == 1U);

        auto lrl = lr->left;
        REQUIRE(lrl->get_key() == 4);
        REQUIRE(lrl->color() == 0U);

        auto right = root->right;
        REQUIRE(right->get_key() == 11);
        REQUIRE(right->color() == 0U);

        auto rl = right->left;
        REQUIRE(rl->get_key() == 8);
        REQUIRE(rl->color() == 1U);

        auto rr = right->right;
        REQUIRE(rr->get_key() == 14);
        REQUIRE(rr->color() == 1U);

        auto rrr = rr->right;
        REQUIRE(rrr->get_key() == 15);
        REQUIRE(rrr->color() == 0U);
      }
    }

    AND_WHEN("inserting an existing item") {
      THEN("it will throw") {
        item_inserter inserter(std::make_unique<int>(existing_key));
        tree_visitor_i<int> &visitor = inserter;

        REQUIRE_THROWS_AS(visitor.visit(root), item_already_exists);
      }
    }
  }
}

inline rb_item<int> *set_up_tree() {
  auto i_15 = new rb_item(std::make_unique<int>(15));
  auto i_14 = new rb_item(std::make_unique<int>(14));
  i_14->increase_color();
  i_14->right = i_15;

  auto i_5 = new rb_item(std::make_unique<int>(5));
  auto i_8 = new rb_item(std::make_unique<int>(8));

  auto i_7 = new rb_item(std::make_unique<int>(7));
  i_7->increase_color();
  i_7->left = i_5;
  i_7->right = i_8;

  auto i_1 = new rb_item(std::make_unique<int>(existing_key));
  i_1->increase_color();

  auto i_2 = new rb_item(std::make_unique<int>(2));
  i_2->left = i_1;
  i_2->right = i_7;

  auto i_11 = new rb_item(std::make_unique<int>(11));
  i_11->increase_color();
  i_11->left = i_2;
  i_11->right = i_14;

  return i_11;
}

} // namespace bbtree::algorithm

#endif // TEST