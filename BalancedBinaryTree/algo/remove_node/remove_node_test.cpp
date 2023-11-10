#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include "remove_node.hpp"

namespace btree::algo {

using rb_node_t = rb_node<int>;
using branch_stack_int = branch_stack_t<int>;

const int existing_key_0 = 0, existing_key_1 = 1, existing_key_3 = 3,
    existing_key_8 = 8, existing_key_9 = 9, non_existing_key = -1;

static typename rb_node_t::node_handle_t set_up_tree();
static rb_node_t& get_top_node(branch_stack_int& branch);

SCENARIO("remove node test", "[remove_node]") {
  GIVEN("a rb-tree") {
    auto root = set_up_tree();

    WHEN("remove a red leaf node") {
      auto remover = remove_node(root,
                                 existing_key_0);
      THEN("it should keep the existing branch structure with the black leaf") {

        auto& branch = remover.get_branch();

        auto& top0 = get_top_node(branch);
        REQUIRE(((int)top0 == 0));
        REQUIRE(top0.color() == 1U); // increase color
        branch.pop();

        auto& top1 = get_top_node(branch);
        REQUIRE(((int)top1 == 1));
        REQUIRE(top1.color() == 1U);
        branch.pop();

        auto& top2 = get_top_node(branch);
        REQUIRE(((int)top2 == 2));
        REQUIRE(top2.color() == 1U);
        branch.pop();

        auto& top5 = get_top_node(branch);
        REQUIRE(((int)top5 == 5));
        REQUIRE(top5.color() == 1U);
        branch.pop();
      }
    }

    WHEN("remove a black node with only one child (must be red)") {
      auto remover = remove_node(root,
                                 existing_key_1);
      THEN("it should replace the black node with its child but black its color") {

        auto& branch = remover.get_branch();
        auto& top0 = get_top_node(branch);
        REQUIRE(((int)top0 == 0));
        REQUIRE(top0.color() == 1U); //black the replaced
        branch.pop();

        auto& top2 = get_top_node(branch);
        REQUIRE(((int)top2 == 2));
        REQUIRE(top2.color() == 1U);
        branch.pop();

        auto& top5 = get_top_node(branch);
        REQUIRE(((int)top5 == 5));
        REQUIRE(top5.color() == 1U);
        branch.pop();
      }
    }

    WHEN("remove a red node with only one black child") {
      auto remover = remove_node(root,
                                 existing_key_3);
      THEN("it should replace the red node with its black child") {

        auto& branch = remover.get_branch();
        auto& top4 = get_top_node(branch);
        REQUIRE(((int)top4 == 4));
        REQUIRE(top4.color() == 1U); //black the replaced
        branch.pop();

        auto& top2 = get_top_node(branch);
        REQUIRE(((int)top2 == 2));
        REQUIRE(top2.color() == 1U);
        branch.pop();

        auto& top5 = get_top_node(branch);
        REQUIRE(((int)top5 == 5));
        REQUIRE(top5.color() == 1U);
        branch.pop();
      }
    }

    WHEN("remove a black leaf node") {
      auto remover = remove_node(root,
                                 existing_key_8);
      THEN("it should double the color of the removed node") {

        auto& branch = remover.get_branch();
        auto& top8 = get_top_node(branch);
        REQUIRE(((int)top8 == 8));
        REQUIRE(top8.color() == 2U); //double the color
        branch.pop();

        auto& top7 = get_top_node(branch);
        REQUIRE(((int)top7 == 7));
        REQUIRE(top7.color() == 1U);
        branch.pop();

        auto& top9 = get_top_node(branch);
        REQUIRE(((int)top9 == 9));
        REQUIRE(top9.color() == 0U);
        branch.pop();

        auto& top5 = get_top_node(branch);
        REQUIRE(((int)top5 == 5));
        REQUIRE(top5.color() == 1U);
        branch.pop();
      }
    }

    WHEN("remove an node with both children") {
      auto remover = remove_node(root,
                                 existing_key_9);
      THEN("it should replace the removed with its closest (greater/equal) descendant "
           "and remove the descendant") {

        auto& branch = remover.get_branch();
        auto& top10 = get_top_node(branch);
        REQUIRE(((int)top10 == 10));
        REQUIRE(top10.color() == 2U); //double the color since it is black (x)
        branch.pop();

        auto& top11 = get_top_node(branch);
        REQUIRE(((int)top11 == 11));
        REQUIRE(top11.color() == 1U);
        branch.pop();

        auto& top10_replace = get_top_node(branch);
        REQUIRE(((int)top10_replace == 10)); //replaced by its closest descendant.
        REQUIRE(top10_replace.color() == 0U);
        branch.pop();

        auto& top5 = get_top_node(branch);
        REQUIRE(((int)top5 == 5));
        REQUIRE(top5.color() == 1U);
        branch.pop();
      }
    }
    WHEN("removing an non-existing node") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(remove_node(root, non_existing_key), item_not_exists);
      }
    }
  }
}

inline typename rb_node_t::node_handle_t set_up_tree() {
  /*
               5(b)
            /         \
        2(b)           9(r)
       /   \          /     \
     1(b)  3(r)    7(b)      11(b)
    /       \      /  \      /   \
   0(r)     4(b) 6(b) 8(b) 10(b) 12(b)
  */

  auto i_0 = std::make_shared<rb_node_t>(existing_key_0);
  auto i_1 = std::make_shared<rb_node_t>(1);
  i_1->increase_color();
  i_1->set_child(i_0, side::left);

  auto i_4 = std::make_shared<rb_node_t>(4);
  i_4->increase_color();
  auto i_3 = std::make_shared<rb_node_t>(3);
  i_3->set_child(i_4, side::right);

  auto i_2 = std::make_shared<rb_node_t>(2);
  i_2->increase_color();
  i_2->set_child(i_1,side::left);
  i_2->set_child(i_3,side::right);

  auto i_6 = std::make_shared<rb_node_t>(6);
  i_6->increase_color();

  auto i_8 = std::make_shared<rb_node_t>(8);
  i_8->increase_color();

  auto i_7 = std::make_shared<rb_node_t>(7);
  i_7->increase_color();
  i_7->set_child(i_6,side::left);
  i_7->set_child(i_8,side::right);

  auto i_10 = std::make_shared<rb_node_t>(10);
  i_10->increase_color();

  auto i_12 = std::make_shared<rb_node_t>(12);
  i_12->increase_color();

  auto i_11 = std::make_shared<rb_node_t>(11);
  i_11->increase_color();
  i_11->set_child(i_10, side::left);
  i_11->set_child(i_12, side::right);

  auto i_9 = std::make_shared<rb_node_t>(9);
  i_9->set_child(i_7, side::left);
  i_9->set_child(i_11, side::right);

  auto i_5 = std::make_shared<rb_node_t>(5);
  i_5->increase_color();
  i_5->set_child(i_2, side::left);
  i_5->set_child(i_9,side::right);

  return i_5;
}

rb_node_t& get_top_node(branch_stack_int& branch) {
  auto&[top, _] = branch.top();
  auto& top_handle = top.get();
  auto node = top_handle.load(std::memory_order_relaxed);
  return *node;
}

} // namespace btree::algo

#endif // TEST