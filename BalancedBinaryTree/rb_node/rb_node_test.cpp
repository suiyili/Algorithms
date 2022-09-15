#ifdef TEST

#include "rb_node.hpp"
#include <catch2/catch_test_macros.hpp>
#include <functional>
#include <memory>

namespace btree::node {

using rb_node_t = rb_node<int>;

SCENARIO("rb node test", "[rb_node]") {

  GIVEN("init data") {
    WHEN("contruct the tree node") {
      rb_node_t node(5);
      THEN("the default color is red") {
        REQUIRE(node.color() == 0U);
      }
    }
  }

  GIVEN("a black parent with one of child is red") {
    rb_node_t parent(5);
    parent.increase_color();

    auto left_child = std::make_shared<rb_node_t>(4);
    parent.set_child(left_child, side::left);

    CHECK(left_child->color() == 0);

    WHEN("pull up color") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(parent.pull_up_color(), color_error);
      }
    }WHEN("push down color") {
      parent.push_down_color();
      THEN("parent decrease color") {
        REQUIRE(parent.color() == 0U);
        AND_THEN("the child will increase color") {
          REQUIRE(left_child->color() == 1U);
        }
      }
    }
  }

  GIVEN("a parent without children") {
    rb_node_t parent(5);

    CHECK_FALSE(parent.get_raw_child(side::left));
    CHECK_FALSE(parent.get_raw_child(side::right));

    WHEN("pull up color") {
      parent.pull_up_color();
      THEN("parent should increase color") {
        REQUIRE(parent.color() == 1U);
      }
    }

    AND_GIVEN("the parent is red") {
      CHECK(parent.color() == 0);
      WHEN("push down color") {
        THEN("it will throw") {
          REQUIRE_THROWS_AS(parent.push_down_color(), color_error);
        }
      }
    }AND_GIVEN("the parent is black") {
      parent.increase_color();
      CHECK(parent.color() == 1);
      WHEN("push down color") {
        parent.push_down_color();
        THEN("parent decrease color") {
          REQUIRE(parent.color() == 0U);
        }
      }
    }
  }

  GIVEN("a black parent with only one black child") {
    rb_node_t parent(5);
    parent.increase_color();

    auto left_child = std::make_shared<rb_node_t>(4);
    parent.set_child(left_child, side::left);
    left_child->increase_color();

    CHECK(parent.color() == 1);
    CHECK_FALSE(parent.get_raw_child(side::right));
    CHECK(left_child->color() == 1);

    WHEN("pull up color") {
      parent.pull_up_color();
      THEN("parent should increase color") {
        REQUIRE(parent.color() == 2U);
      }AND_THEN("children will decrease color") {
        REQUIRE(left_child->color() == 0);
      }
    }

    WHEN("push down color") {
      parent.push_down_color();
      THEN("parent decrease color") {
        REQUIRE(parent.color() == 0U);
        AND_THEN("the child will increase color") {
          REQUIRE(left_child->color() == 2U);
        }
      }
    }
  }

  GIVEN("a parent with both children") {
    auto root = rb_node_t(0);
    auto parent = std::make_shared<rb_node_t>(5);
    root.set_child(parent, side::right);

    auto left_child = std::make_shared<rb_node_t>(4);
    parent->set_child(left_child, side::left);
    left_child->increase_color();

    auto right_child = std::make_shared<rb_node_t>(6);
    parent->set_child(right_child, side::right);

    CHECK(parent->color() == 0);
    CHECK(parent->get_child(side::left));
    CHECK(parent->get_child(side::right));
    CHECK(left_child->color() == 1);
    CHECK(right_child->color() == 0);

    WHEN("rotate with the black child") {
      THEN("it should throw") {
        REQUIRE_THROWS_AS(root.rotate(side::right, side::left), rotate_error);
      }
    }WHEN("rotate with the red child") {
      parent->increase_color();
      root.rotate(side::right, side::right);
      THEN("it should switch parent child position") {
        auto new_parent = root.get_child(side::right);
        REQUIRE((rb_node_t::value_type_t) * new_parent == (rb_node_t::value_type_t) * right_child);
        auto new_left = new_parent->get_child(side::left);
        REQUIRE((rb_node_t::value_type_t) * new_left == (rb_node_t::value_type_t) * parent);
        AND_THEN("it also should swtich their color") {
          REQUIRE(new_parent->color() == 1);
          REQUIRE(parent->color() == 0);
        }
      }
    }
  }
}

} // namespace btree::node

#endif // TEST