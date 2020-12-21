#ifdef TEST

#include <catch2/catch.hpp>
#include "graft_for_removing.hpp"

namespace bbtree::algorithm {

SCENARIO("graft for removing test", "[graft_for_removing]") {

  GIVEN("no x child") {
    rb_item parent(std::make_unique<int>(3));
    parent.increase_color();
    auto root_ptr = &parent;
    item_handle root(root_ptr);

    rb_item x_child(std::make_unique<int>(1));
    x_child.increase_color();
    parent.left = &x_child;

    rb_item right_child(std::make_unique<int>(7));
    parent.right = &right_child;

    CHECK(x_child.color() == 1U);
    CHECK(right_child.color() == 0U);

    WHEN("graft") {
      THEN("it will do nothing") {
        REQUIRE_NOTHROW(graft_for_removing(root));
      }
    }
  }

  GIVEN("a x child and red sibling") {
    rb_item parent(std::make_unique<int>(3));
    parent.increase_color();
    auto root_ptr = &parent;
    item_handle root(root_ptr);

    rb_item x_child(std::make_unique<int>(1));
    x_child.increase_color();
    x_child.increase_color();
    parent.left = &x_child;

    rb_item right_child(std::make_unique<int>(7));
    parent.right = &right_child;

    CHECK(x_child.color() == 2U);
    CHECK(right_child.color() == 0U);

    WHEN("graft x child") {
      graft_for_removing(root);
     
      THEN("it will rotate the red to parent and increase its color") {
        REQUIRE(root->get_key() == right_child.get_key());
        REQUIRE(root->color() == 1);
      }
      AND_THEN("it will decrease x child color") {
        REQUIRE(x_child.color() == 1U);
      }
      AND_THEN("it will keep x parent color") {
        REQUIRE(parent.color() == 1U);
      }
    }
  }

  GIVEN("x child and black sibling and two black nephew") {
    rb_item parent(std::make_unique<int>(3));
    auto root_ptr = &parent;
    item_handle root(root_ptr);

    rb_item x_child(std::make_unique<int>(1));
    x_child.increase_color();
    x_child.increase_color();
    parent.left = &x_child;

    rb_item right_child(std::make_unique<int>(7));
    right_child.increase_color();
    parent.right = &right_child;

    rb_item rl_grand(std::make_unique<int>(6));
    rl_grand.increase_color();
    right_child.left = &rl_grand;

    rb_item rr_grand(std::make_unique<int>(8));
    rr_grand.increase_color();
    right_child.right = &rr_grand;

    CHECK(parent.color() == 0U);
    CHECK(x_child.color() == 2U);
    CHECK(right_child.color() == 1U);
    CHECK(rl_grand.color() == 1U);
    CHECK(rr_grand.color() == 1U);

    WHEN("graft x child") {
      graft_for_removing(root);

      THEN("it should pull up color to parent") {
        REQUIRE(root->color() == 1U);
      }
      AND_THEN("it will decrease x child color") {
        REQUIRE(x_child.color() == 1U);
      }
      AND_THEN("it will increase x parent color") {
        REQUIRE(parent.color() == 1U);
      }
    }
  }

  GIVEN("x child and black sibling and closest nephew is red") {
    rb_item parent(std::make_unique<int>(3));
    auto root_ptr = &parent;
    item_handle root(root_ptr);

    rb_item x_child(std::make_unique<int>(1));
    x_child.increase_color();
    x_child.increase_color();
    parent.left = &x_child;

    rb_item right_child(std::make_unique<int>(7));
    right_child.increase_color();
    parent.right = &right_child;

    rb_item rl_grand(std::make_unique<int>(5));
    right_child.left = &rl_grand;

    rb_item rll_great(std::make_unique<int>(4));
    rll_great.increase_color();
    rl_grand.left = &rll_great;

    rb_item rlr_great(std::make_unique<int>(6));
    rlr_great.increase_color();
    rl_grand.right = &rlr_great;

    rb_item rr_grand(std::make_unique<int>(8));
    rr_grand.increase_color();
    right_child.right = &rr_grand;

    CHECK(parent.color() == 0U);
    CHECK(x_child.color() == 2U);
    CHECK(right_child.color() == 1U);
    CHECK(rl_grand.color() == 0U);
    CHECK(rr_grand.color() == 1U);

    WHEN("graft x child") {
      graft_for_removing(root);

      THEN("it will rotate closest nephew as parent") {
        REQUIRE(root->get_key() == rl_grand.get_key());
      }
      AND_THEN("it will decrease x child color") {
        REQUIRE(x_child.color() == 1U);
      }
    }
  }
}

} // namespace bbtree::algorithm
#endif // TEST