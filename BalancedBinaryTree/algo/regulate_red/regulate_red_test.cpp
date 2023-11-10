#ifdef TEST

#include "regulate_red.hpp"
#include <catch2/catch_test_macros.hpp>

namespace btree::algo {

using rb_node_t = rb_node<int>;
using branch_stack_int = branch_stack_t<int>;

using rb_node_shared_t = rb_node_t::shared_node_t;
using rb_node_handle_t = rb_node_t::node_handle_t;

class tree_with_three_level final {
public:
  tree_with_three_level();

  rb_node_handle_t &get_root();
  rb_node_shared_t get_parent();
  rb_node_shared_t get_child(side which);
  rb_node_shared_t get_grand_child(side which_child, side which_grand);
private:
  rb_node_handle_t root_;
};

SCENARIO("regulate red test", "[regulate_red]") {

  GIVEN("a pair of consecutive red nodes on the branch") {
    tree_with_three_level tree;
    auto parent = tree.get_parent();

    auto left_child = tree.get_child(side::left);
    left_child->decrease_color();
    auto left_right_grand = tree.get_grand_child(side::left, side::right);
    left_right_grand->decrease_color();

    branch_stack_int branch;
    branch.emplace(tree.get_root(), side::left);
    branch.emplace(parent->get_child_handle(side::left), side::left);
    branch.emplace(left_child->get_child_handle(side::right), side::right);

    CHECK(left_child->color() == 0);
    CHECK(left_right_grand->color() == 0);

    auto right_child = tree.get_child(side::right);

    AND_GIVEN("the sibling of consecutive red nodes is red") {
      right_child->decrease_color();
      CHECK(right_child->color() == 0);

      WHEN("regulate the consecutive red nodes") {
        regulate_red<int>(branch);
        THEN("the old root will push down color") {
          auto graft_parent = tree.get_parent();
          REQUIRE((int)*graft_parent == (int)*parent); //kept old parent
          REQUIRE(graft_parent->color() == 1U);// push down color but then be assigned black since it is root.
          auto graft_left_child = tree.get_child(side::left);
          REQUIRE((int)*graft_left_child == (int)*left_child);
          REQUIRE(graft_left_child->color() == 1U);
          auto graft_right_child = tree.get_child(side::right);
          REQUIRE((int)*graft_right_child == (int)*right_child);
          REQUIRE(graft_right_child->color() == 1U);
        }
      }
    }AND_GIVEN("the sibling is black") {
      CHECK(right_child->color() == 1);
      WHEN("regulate the consecutive red nodes") {
        regulate_red<int>(branch);
        THEN("root will rotate the consecutive red nodes") {
          auto graft_parent = tree.get_parent();
          REQUIRE((int)*graft_parent == (int)*left_right_grand); //atomic copy
          REQUIRE(graft_parent->color() == 1U);

          auto graft_left_child = tree.get_child(side::left);
          REQUIRE((int)*graft_left_child == (int)*left_child);
          REQUIRE(graft_left_child->color() == 0U);

          auto graft_right_child = tree.get_child(side::right);
          REQUIRE((int)*graft_right_child == (int)*parent);
          REQUIRE(graft_right_child->color() == 0U);
        }
      }
    }
  }

  GIVEN("no consecutive red nodes on a given branch") {
    tree_with_three_level tree;
    auto parent = tree.get_parent();
    auto left_child = tree.get_child(side::left);
    auto left_right_grand = tree.get_grand_child(side::left, side::right);
    left_right_grand->decrease_color();

    branch_stack_int branch;
    branch.emplace(tree.get_root(), side::left);
    branch.emplace(parent->get_child_handle(side::left), side::left);
    branch.emplace(left_child->get_child_handle(side::right), side::right);

    CHECK(left_child->color() == 1);
    CHECK(left_right_grand->color() == 0);

    WHEN("regulate the nodes") {
      regulate_red<int>(branch);
      THEN("tree hierarchy should not be changed") {
        REQUIRE((int)*parent == 4);
        REQUIRE(parent->color() == 1);

        REQUIRE((int)*left_child == 2);
        REQUIRE(left_child->color() == 1);

        REQUIRE((int)*left_right_grand == 3);
        REQUIRE(left_right_grand->color() == 0);
      }
    }
  }
}

tree_with_three_level::tree_with_three_level()
    : root_(std::make_shared<rb_node_t>(4)) {
  /*
                   4(b)
                /       \
               2(b)     6(b)
              /   \    /   \
            1(b) 3(b) 5(b) 7(b)
   */
  auto parent = root_.load(std::memory_order_acquire);
  parent->increase_color();

  auto left_child = std::make_shared<rb_node_t>(2);
  left_child->increase_color();
  parent->set_child(left_child, side::left);

  auto right_child = std::make_shared<rb_node_t>(6);
  right_child->increase_color();
  parent->set_child(right_child, side::right);

  auto left_left_grand = std::make_shared<rb_node_t>(1);
  left_left_grand->increase_color();
  left_child->set_child(left_left_grand, side::left);
  auto left_right_grand = std::make_shared<rb_node_t>(3);
  left_right_grand->increase_color();
  left_child->set_child(left_right_grand, side::right);

  auto right_left_grand = std::make_shared<rb_node_t>(5);
  right_left_grand->increase_color();
  right_child->set_child(right_left_grand, side::left);
  auto right_right_grand = std::make_shared<rb_node_t>(7);
  right_right_grand->increase_color();
  right_child->set_child(right_right_grand, side::right);

}
rb_node_handle_t& tree_with_three_level::get_root() {
  return root_;
}

rb_node_shared_t tree_with_three_level::get_parent() {
  return root_.load(std::memory_order_relaxed);
}

rb_node_shared_t tree_with_three_level::get_child(side which) {
  auto parent = root_.load(std::memory_order_relaxed);
  return parent->get_child(which);
}

rb_node_shared_t tree_with_three_level::get_grand_child(side which_child, side which_grand) {
  auto parent = root_.load(std::memory_order_relaxed);
  auto child = parent->get_child(which_child);
  return child->get_child(which_grand);
}

} // namespace btree::algo

#endif // TEST