#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include "insert_node.hpp"

namespace btree::algo {

using rb_node_t = rb_node<int>;
using branch_stack_int = branch_stack_t<int>;

const int existing_key = 1;
static typename rb_node_t::node_handle_t set_up_tree();

static rb_node_t& get_top_node(branch_stack_int& branch);

SCENARIO("insert node test", "[insert_node]") {
  GIVEN("a rb-tree with items setup") {
    auto root = set_up_tree();

    WHEN("inserting a new node") {
      auto key_to_insert = 4;
      auto branch = insert_node<int>(root, std::make_unique<rb_node_t>(key_to_insert));
      THEN("it should get the branch with the insert node") {
        /*
          expected result:
                 11(b)
                /
              2(r)
                  \
                  7(b)
                 /
               5(r)
              /
            4(r)

        */
        auto& inserted = get_top_node(branch);
        REQUIRE((int)inserted == key_to_insert);
        REQUIRE(inserted.color() == 0U);
        branch.pop();

        auto& leaf = get_top_node(branch);
        REQUIRE(((int)leaf == 5));
        REQUIRE(leaf.color() == 0U);
        branch.pop();

        auto& stem1 = get_top_node(branch);
        REQUIRE(((int)stem1 == 7));
        REQUIRE(stem1.color() == 1U);
        branch.pop();

        auto& stem2 = get_top_node(branch);
        REQUIRE(((int)stem2 == 2));
        REQUIRE(stem2.color() == 0U);
        branch.pop();

        auto& root_node = get_top_node(branch);
        REQUIRE(((int)root_node == 11));
        REQUIRE(root_node.color() == 1U);
        branch.pop();
      }
    }

    AND_WHEN("inserting an existing node") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(insert_node<int>(root, std::make_unique<rb_node_t>(existing_key)), item_already_exists);
      }
    }
  }
}

inline typename rb_node_t::node_handle_t set_up_tree() {
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

  return typename rb_node_t::node_handle_t{i_11};
}

rb_node_t& get_top_node(branch_stack_int& branch) {
  auto&[top, _] = branch.top();
  auto& top_handle = top.get();
  auto node = top_handle.load(std::memory_order_relaxed);
  return *node;
}

} // namespace btree::algo

#endif // TEST