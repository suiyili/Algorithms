#ifdef TEST

#include <catch2/catch.hpp>
#include "rb_item.hpp"

namespace bbtree::item {

SCENARIO("rb item test", "[rb_item]") {

  GIVEN("init data") {
    WHEN("contruct the tree item") {
      rb_item item(std::make_unique<int>(5));
      THEN("the default color is red") { REQUIRE(item.color() == 0U); }
    }
  }

  GIVEN("a red parent and two red children") {
    rb_item parent(std::make_unique<int>(5));

    rb_item left_child(std::make_unique<int>(4));
    parent.left = &left_child;
    rb_item right_child(std::make_unique<int>(6));
    parent.right = &right_child;

    WHEN("check red_status") {
      THEN("it should throw") {
        REQUIRE_THROWS_AS(parent.red_status(), color_error);
      }
    }
  }

  GIVEN("a red parent with both black children") {
    rb_item parent(std::make_unique<int>(5));

    rb_item left_child(std::make_unique<int>(4));
    left_child.increase_color();
    parent.left = &left_child;

    CHECK(left_child.color() > 0);

    WHEN("check red_status") {
      auto red_status = parent.red_status();
      THEN("it should be parent") { REQUIRE(red_status == item_status::parent); }
    }
  }

  GIVEN("a black parent and two red children") {
    rb_item parent(std::make_unique<int>(5));
    parent.increase_color();

    rb_item left_child(std::make_unique<int>(4));
    parent.left = &left_child;
    rb_item right_child(std::make_unique<int>(6));
    parent.right = &right_child;

    CHECK(parent.color() > 0);
    CHECK(left_child.color() == 0);
    CHECK(right_child.color() == 0);

    WHEN("check red_status") {
      auto red_status = parent.red_status();
      THEN("it should be children") { REQUIRE(red_status == item_status::children); }
    }
  }

  GIVEN("a red parent with only left red child") {
    rb_item parent(std::make_unique<int>(5));

    rb_item left_child(std::make_unique<int>(4));
    parent.left = &left_child;
    rb_item right_child(std::make_unique<int>(6));
    right_child.increase_color();
    parent.right = &right_child;

    CHECK(parent.color() == 0);
    CHECK(left_child.color() == 0);

    WHEN("check red_status") {
      auto red_status = parent.red_status();
      THEN("it should be the left child") { REQUIRE(red_status == item_status::lchild); }
    }
  }

  GIVEN("a black parent with only right red child") {
    rb_item parent(std::make_unique<int>(5));
    parent.increase_color();

    rb_item right_child(std::make_unique<int>(6));
    parent.right = &right_child;

    CHECK(parent.color() > 0);
    CHECK(right_child.color() == 0);

    WHEN("check red_status") {
      auto red_status = parent.red_status();
      THEN("it should be the right child") { REQUIRE(red_status == item_status::rchild); }
    }
  }

  GIVEN("a black parent and two black children") {
    rb_item parent(std::make_unique<int>(5));
    parent.increase_color();

    rb_item left_child(std::make_unique<int>(4));
    left_child.increase_color();
    parent.left = &left_child;
    rb_item right_child(std::make_unique<int>(6));
    right_child.increase_color();
    parent.right = &right_child;

    CHECK(parent.color() > 0);
    CHECK(left_child.color() > 0);
    CHECK(right_child.color() > 0);

    WHEN("check red_status") {
      auto red_status = parent.red_status();
      THEN("it should be none") { REQUIRE(red_status == item_status::none); }
    }
  }

  GIVEN("a parent with at least one red child") {
    rb_item parent(std::make_unique<int>(5));
    parent.increase_color();
    rb_item left_child(std::make_unique<int>(4));
    parent.left = &left_child;

    CHECK(parent.red_status() == item_status::lchild);

    WHEN("it pull up") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(parent.pull_up_color(), color_error);
      }
    }
  }

  GIVEN("a parent without children") {
    rb_item parent(std::make_unique<int>(5));
    CHECK(parent.red_status() == item_status::parent);

    WHEN("pull up") {
      parent.pull_up_color();
      THEN("parent should increase color") { REQUIRE(parent.color() == 1U); }
    }
  }

  GIVEN("a parent with at least a black child") {
    rb_item parent(std::make_unique<int>(5));

    rb_item left_child(std::make_unique<int>(4));
    parent.left = &left_child;
    left_child.increase_color();

    CHECK(parent.color() == 0);
    CHECK(left_child.color() == 1);

    WHEN("pull up") {
      parent.pull_up_color();
      THEN("parent should increase color") { REQUIRE(parent.color() == 1U); }
      AND_THEN("children will decrease color") {
        REQUIRE(left_child.color() == 0);
      }
    }
  }

  GIVEN("a red parent") {
    rb_item parent(std::make_unique<int>(5));
    CHECK(parent.red_status() == item_status::parent);

    WHEN("push down") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(parent.push_down_color(), color_error);
      }
    }
  }

  GIVEN("a black parent without children") {
    rb_item parent(std::make_unique<int>(5));
    parent.increase_color();
    CHECK(parent.red_status() == item_status::none);

    WHEN("push down") {
      parent.push_down_color();

      THEN("parent decrease color") { REQUIRE(parent.color() == 0U); }
    }
  }

  GIVEN("a black parent with at least one child") {
    rb_item parent(std::make_unique<int>(5));
    parent.increase_color();
    rb_item left_child(std::make_unique<int>(4));
    parent.left = &left_child;

    CHECK(parent.color() == 1U);
    CHECK(left_child.color() == 0U);

    WHEN("push down") {
      parent.push_down_color();

      THEN("parent decrease color") { REQUIRE(parent.color() == 0U); }
      AND_THEN("the child will increase color") {
        REQUIRE(left_child.color() == 1U);
      }
    }
  }

  GIVEN("two rb item") {
    rb_item rb1(std::make_unique<int>(5));
    rb_item rb2(std::make_unique<int>(4));
    WHEN("swap their values") { 
      swap_value(rb1, rb2);
      THEN("their value shoudl be swapped") { 
        REQUIRE(rb1.get_key() == 4);
        REQUIRE(rb2.get_key() == 5);
      }
    }

  }
}

} // namespace bbtree::item

#endif // TEST