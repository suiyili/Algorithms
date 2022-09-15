#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include "node_inserter.hpp"

namespace btree::algorithm {

using rb_node_t = rb_node<int>;
using node_inserter_t = node_inserter<int>;

const int existing_key = 1;
static typename rb_node_t::shared_rb_node_t set_up_tree();

SCENARIO("node inserter test", "[node_inserter]") {
  GIVEN("a rb-tree with items setup") {
    auto root = set_up_tree();

    WHEN("inserting a new node") {
      const int key_to_insert = 4;
      node_inserter_t inserter(key_to_insert);
      tree_visitor_i<int> &visitor = inserter;
      root = visitor.visit(root);

      THEN("it should follow red black tree insert rule") {
        /*
          expected result:
                   7(b)
                /        \
              2(r)       11(r)
             /   \      /    \
           1(b)  5(b)  8(b)  14(b)
                 /            \
                4(r)          15(r)

        */
        REQUIRE(((int)*root == 7));
        REQUIRE(root->color() == 1U);

        auto left = root->get_child(side::left);
        REQUIRE(((int)*left == 2));
        REQUIRE(left->color() == 0U);

        auto ll = left->get_child(side::left);
        REQUIRE(((int)*ll == existing_key));
        REQUIRE(ll->color() == 1U);

        auto lr = left->get_child(side::right);
        REQUIRE(((int)*lr == 5));
        REQUIRE(lr->color() == 1U);

        auto lrl = lr->get_child(side::left);
        REQUIRE(((int)*lrl == 4));
        REQUIRE(lrl->color() == 0U);

        auto right = root->get_child(side::right);
        REQUIRE(((int)*right == 11));
        REQUIRE(right->color() == 0U);

        auto rl = right->get_child(side::left);
        REQUIRE(((int)*rl == 8));
        REQUIRE(rl->color() == 1U);

        auto rr = right->get_child(side::right);
        REQUIRE(((int)*rr == 14));
        REQUIRE(rr->color() == 1U);

        auto rrr = rr->get_child(side::right);
        REQUIRE(((int)*rrr == 15));
        REQUIRE(rrr->color() == 0U);
      }
    }

    AND_WHEN("inserting an existing node") {
      THEN("it will throw") {
        node_inserter_t inserter(existing_key);
        tree_visitor_i<int> &visitor = inserter;

        REQUIRE_THROWS_AS(visitor.visit(root), item_already_exists);
      }
    }
  }
}

inline typename rb_node_t::shared_rb_node_t set_up_tree() {
  /*
                     11(b)
                   /       \
                2(r)        14(b)
               /   \         \
             1(b)  7(b)      15(r)
                  /   \
                5(r)  8(r)

  */
  auto i_15 = std::make_shared<rb_node_t>(15);
  auto i_14 = std::make_shared<rb_node_t>(14);
  i_14->increase_color();
  i_14->set_child(i_15, side::right);

  auto i_5 = std::make_shared<rb_node_t>(5);
  auto i_8 = std::make_shared<rb_node_t>(8);

  auto i_7 = std::make_shared<rb_node_t>(7);
  i_7->increase_color();
  i_7->set_child(i_5, side::left);
  i_7->set_child(i_8, side::right);

  auto i_1 = std::make_shared<rb_node_t>(existing_key);
  i_1->increase_color();

  auto i_2 = std::make_shared<rb_node_t>(2);
  i_2->set_child(i_1, side::left);
  i_2->set_child(i_7, side::right);

  auto i_11 = std::make_shared<rb_node_t>(11);
  i_11->increase_color();
  i_11->set_child(i_2, side::left);
  i_11->set_child(i_14, side::right);

  return i_11;
}

} // namespace btree::algorithm

#endif // TEST