#ifdef TEST

#include "dual_black_regulator.hpp"
#include <catch2/catch_test_macros.hpp>

namespace btree::algorithm {

using rb_node_t = rb_node<int>;

SCENARIO("dual black regulator test", "[dual_black_regulator]") {

  GIVEN("x child is single black") {
    /*
     *              3(b)
     *             / \
     *           1(b) 7(b)
     *                / \
     *             5(b) 8(b)
     * */
    auto root = std::make_shared<rb_node_t>(0); //dummy
    auto parent = std::make_shared<rb_node_t>(3);
    parent->increase_color();
    root->set_child(parent, side::left);

    auto x_child = std::make_shared<rb_node_t>(1);
    x_child->increase_color();
    parent->set_child(x_child, side::left);

    auto right_child = std::make_shared<rb_node_t>(7);
    right_child->increase_color();
    parent->set_child(right_child, side::right);

    auto nephew_left = std::make_shared<rb_node_t>(5);
    nephew_left->increase_color();
    right_child->set_child(nephew_left, side::left);

    auto nephew_right = std::make_shared<rb_node_t>(8);
    nephew_right->increase_color();
    right_child->set_child(nephew_right, side::right);

    CHECK(x_child->color() == 1U);
    CHECK(right_child->color() == 1U);
    AND_GIVEN("force it as dual black") {
      dual_black_regulator<int> regulator(side::left, true);
      WHEN("regulate x child") {
        THEN("it will regulate color") {
          REQUIRE(regulator.regulate(root, side::left));
        }
      }
    }AND_GIVEN("it as single black") {
      dual_black_regulator<int> regulator(side::left, false);
      WHEN("regulate x child") {
        THEN("it will do nothing") {
          REQUIRE_FALSE(regulator.regulate(root, side::left));
        }
      }
    }
  }

  GIVEN("x child and red sibling") {
    /*         3(b)
     *        /    \
     *     1(2b)   7(r)
     *            /   \
     *          6(b)  8(b)
     * */
    auto root = std::make_shared<rb_node_t>(0); //dummy value
    auto parent = std::make_shared<rb_node_t>(3);
    parent->increase_color();
    root->set_child(parent, side::left);

    auto x_child = std::make_shared<rb_node_t>(1);
    x_child->increase_color();
    x_child->increase_color();
    parent->set_child(x_child, side::left);

    auto right_child = std::make_shared<rb_node_t>(7);
    parent->set_child(right_child, side::right);

    auto rl_grand = std::make_shared<rb_node_t>(6);
    rl_grand->increase_color();
    right_child->set_child(rl_grand, side::left);

    auto rr_grand = std::make_shared<rb_node_t>(8);
    rr_grand->increase_color();
    right_child->set_child(rr_grand, side::right);

    CHECK(parent->color() == 1U);
    CHECK(x_child->color() == 2U);
    CHECK(right_child->color() == 0U);
    CHECK(rl_grand->color() == 1U);
    CHECK(rr_grand->color() == 1U);

    WHEN("regulate x child") {
      dual_black_regulator<int> regulator(side::left);
      regulator.regulate(root, side::left);
      /*       7(b)
     *        /    \
     *       3(b)  8(b)
     *      /    \
     *   1(b)    6(r)
     *
     * */

      parent = root->get_child(side::left);
      auto old_parent = parent->get_child(side::left);
      THEN("it will rotate the red sibling to top") {
        REQUIRE((int) *parent == 7);
        AND_THEN("it will increase its color") {
          REQUIRE(parent->color() == 1);
        }
      }AND_THEN("it will decrease x child color") {
        x_child = old_parent->get_child(side::left);
        REQUIRE(x_child->color() == 1U);
      }AND_THEN("it will keep old parent its color") {
        // parent becomes new x node and regulate again.
        // but not a dual black.
        REQUIRE(old_parent->color() == 1U);
      }
    }
  }

  GIVEN("x child and black sibling") {
    /*         3(b)
     *        /    \
     *     1(2b)   7(b)
     *            /    \
     *         5(r/b)  8(b)
     * */
    auto root = std::make_shared<rb_node_t>(0); //dummy value
    auto parent = std::make_shared<rb_node_t>(3);
    root->set_child(parent, side::left);

    auto x_child = std::make_shared<rb_node_t>(1);
    x_child->increase_color();
    x_child->increase_color();
    parent->set_child(x_child,side::left);

    auto right_child = std::make_shared<rb_node_t>(7);
    right_child->increase_color();
    parent->set_child(right_child, side::right);

    auto rl_grand = std::make_shared<rb_node_t>(5);
    right_child->set_child(rl_grand, side::left);

    auto rr_grand= std::make_shared<rb_node_t>(8);
    rr_grand->increase_color();
    right_child->set_child(rr_grand, side::right);

    CHECK(parent->color() == 0U);
    CHECK(x_child->color() == 2U);
    CHECK(right_child->color() == 1U);

    AND_GIVEN("two nephews are black") {
      /*           \
       *           7(b)
       *          /    \
       *         5(b)  8(b)
       * */
      rl_grand->increase_color();

      CHECK(rl_grand->color() == 1U);
      CHECK(rr_grand->color() == 1U);

      WHEN("regulate x child") {

        /*         3(2b)
         *        /    \
         *     1(b)   7(r)
         *            /   \
         *          6(b)  8(b)
         * */
        dual_black_regulator<int> regulator(side::left);
        regulator.regulate(root, side::left);

        parent = root->get_child(side::left);
        THEN("it should pull up color to parent") {
          REQUIRE((int)*parent == 3);
          REQUIRE(parent->color() == 1U);
        }THEN("it will decrease x child color") {
          x_child = parent->get_child(side::left);
          REQUIRE((int)*x_child == 1);
          REQUIRE(x_child->color() == 1U);
        }THEN("it will decrease x nephew color") {
          right_child = parent->get_child(side::right);
          REQUIRE((int)*right_child == 7);
          REQUIRE(right_child->color() == 0U);
        }
      }
    }

    AND_GIVEN("only its far nephew is black") {
      /*           \
       *           7(b)
       *          /    \
       *         5(r)  8(b)
       *        /   \
       *      4(b)  6(b)
       * */

      auto rll_great = std::make_shared<rb_node_t>(4);
      rll_great->increase_color();
      rl_grand->set_child(rll_great, side::left);

      auto rlr_great = std::make_shared<rb_node_t>(6);
      rlr_great->increase_color();
      rl_grand->set_child(rlr_great, side::right);

      CHECK(rl_grand->color() == 0U);
      CHECK(rr_grand->color() == 1U);

      WHEN("regulate x child") {
        dual_black_regulator<int> regulator(side::left);
        regulator.regulate(root, side::left);
         /*           5(b)
          *         /      \
          *      3(b)      7(b)
          *     /   \     /   \
          *  1(b)  4(b)  6(b)  8(b)
        * */
        // two red nodes 3->5(right) happens during operation.
        parent = root->get_child(side::left);
        auto left_child = parent->get_child(side::left);
        THEN("it will rotate closest nephew as parent") {
          REQUIRE((int)*parent == 5);
          REQUIRE(parent->color() == 0);
        }THEN("the old parent will become left child") {
          REQUIRE((int)*left_child == 3); //old parent
          REQUIRE(left_child->color() == 1);
        }THEN("right child will remain") {
          right_child = parent->get_child(side::right);
          REQUIRE((int)*right_child == 7);
          REQUIRE(right_child->color() == 1U);
        }THEN("it will decrease x child color") {
          auto ll_grand = left_child->get_child(side::left);
          REQUIRE((int)*ll_grand == 1); //old x child
          REQUIRE(ll_grand->color() == 1U);
        }
      }
    }
  }
}

} // namespace btree::algorithm
#endif // TEST