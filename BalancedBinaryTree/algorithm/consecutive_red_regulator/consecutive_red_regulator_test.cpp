#ifdef TEST

#include "consecutive_red_regulator.hpp"
#include <catch2/catch_test_macros.hpp>

namespace btree::algorithm {

using rb_node_t = rb_node<int>;

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

SCENARIO("regulate consecutive red test", "[regulate_consecutive_red]") {

  GIVEN("a pair of consecutive red nodes") {
    tree_with_three_level tree;
    auto parent = tree.get_parent();

    auto left_child = tree.get_child(side::left);
    left_child->decrease_color();
    auto left_right_grand = tree.get_grand_child(side::left, side::right);
    left_right_grand->decrease_color();

    CHECK(left_child->color() == 0);
    CHECK(left_right_grand->color() == 0);

    auto right_child = tree.get_child(side::right);

    AND_GIVEN("the sibling of them is red") {
      right_child->decrease_color();
      CHECK(right_child->color() == 0);

      WHEN("regulate the consecutive red nodes") {
        consecutive_red_regulator<int> regulator;
        auto regulated = regulator.regulate(left_child->get_child_handle(side::right), side::right);
        regulated &= regulator.regulate(parent->get_child_handle(side::left), side::left);
        regulated &= regulator.regulate(tree.get_root(), side::left);

        THEN("root will push down color") {
          REQUIRE(regulated);
          auto graft_parent = tree.get_parent();
          REQUIRE(graft_parent->color() == 0U);
          auto graft_left_child = tree.get_child(side::left);
          REQUIRE(graft_left_child->color() == 1U);
          auto graft_right_child = tree.get_child(side::right);
          REQUIRE(graft_right_child->color() == 1U);
        }
      }
    }AND_GIVEN("the sibling is black") {
      CHECK(right_child->color() == 1);
      WHEN("regulate the consecutive red nodes") {
        consecutive_red_regulator<int> regulator;
        auto regulated = regulator.regulate(left_child->get_child_handle(side::right), side::right);
        regulated &= regulator.regulate(parent->get_child_handle(side::left), side::left);
        regulated &= regulator.regulate(tree.get_root(), side::left);

        THEN("root will rotate the consecutive red nodes") {
          REQUIRE(regulated);
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

  GIVEN("no consecutive red nodes") {
    tree_with_three_level tree;
    auto parent = tree.get_parent();
    auto left_child = tree.get_child(side::left);
    auto left_right_grand = tree.get_grand_child(side::left, side::right);
    left_right_grand->decrease_color();

    CHECK(left_child->color() == 1);
    CHECK(left_right_grand->color() == 0);

    WHEN("regulate the nodes") {
      consecutive_red_regulator<int> regulator;
      auto regulated = regulator.regulate(left_child->get_child_handle(side::right), side::right);
      regulated &= regulator.regulate(parent->get_child_handle(side::left), side::left);
      THEN("it should failed") {
        REQUIRE_FALSE(regulated);
      }
    }
  }
}

tree_with_three_level::tree_with_three_level()
    : root_(std::make_shared<rb_node_t>(4)) {
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

} // namespace btree::algorithm

#endif // TEST