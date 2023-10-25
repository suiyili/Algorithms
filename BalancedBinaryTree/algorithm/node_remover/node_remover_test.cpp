#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include "node_remover.hpp"

namespace btree::algorithm {

using rb_node_t = rb_node<int>;

const int existing_key_0 = 0, existing_key_1 = 1,
    existing_key_7 = 7, existing_key_8 = 8, non_existing_key = -1;

static typename rb_node_t::node_handle_t set_up_tree();
static typename rb_node_t::node_handle_t set_up_tree_for_case1();
static typename rb_node_t::node_handle_t set_up_tree_for_case2();
static typename rb_node_t::node_handle_t set_up_tree_for_case3();
static typename rb_node_t::node_handle_t set_up_tree_for_case4();

SCENARIO("node remover test", "[node_remover]") {
  GIVEN("a rb-tree") {
    auto root = set_up_tree();

    WHEN("remove an node with left red leaf") {
      const int key_to_remove = existing_key_1;
      node_remover remover(key_to_remove);
      tree_visitor_i<int> &visitor = remover;
      visitor.visit(root);
      THEN("it should keep the existing structure") {
        auto parent = root.load(std::memory_order_acquire);
        REQUIRE(((int)*parent == 4));
        REQUIRE(parent->color() == 1U);

        auto left = parent->get_child(side::left);
        REQUIRE(((int)*left == 2));
        REQUIRE(left->color() == 1U);

        auto right = parent->get_child(side::right);
        REQUIRE(((int)*right == 8));
        REQUIRE(right->color() == 0U);

        auto ll = left->get_child(side::left);
        REQUIRE(((int)*ll == 0));
        REQUIRE(ll->color() == 1U);

        auto lr = left->get_child(side::right);
        REQUIRE(((int)*lr == 3));
        REQUIRE(lr->color() == 1U);

        auto lll = ll->get_child(side::left);
        REQUIRE_FALSE((lll));
      }
    }

    WHEN("remove an node with both children") {
      const int key_to_remove = existing_key_8;
      node_remover remover(key_to_remove);
      tree_visitor_i<int> &visitor = remover;
      visitor.visit(root);
      THEN("it should switch key with its close value descendant") {
        auto parent = root.load(std::memory_order_acquire);
        REQUIRE(((int)*parent == 4));
        REQUIRE(parent->color() == 1U);

        auto left = parent->get_child(side::left);
        REQUIRE(((int)*left == 2));
        REQUIRE(left->color() == 1U);

        auto right = parent->get_child(side::right);
        REQUIRE(((int)*right == 9));
        REQUIRE(right->color() == 1U);

        auto rl = right->get_child(side::left);
        REQUIRE(((int)*rl == 6));
        REQUIRE(rl->color() == 0U);

        auto rr = right->get_child(side::right);
        REQUIRE(((int)*rr == 10));
        REQUIRE(rr->color() == 1U);

        auto rrl = rr->get_child(side::left);
        REQUIRE_FALSE((rrl));

        auto rrr = rr->get_child(side::right);
        REQUIRE(((int)*rrr == 11));
        REQUIRE(rrr->color() == 0U);
      }
    }
  }

  GIVEN("a rb-tree with case 1 items setup") {
    auto root = set_up_tree_for_case1();

    WHEN("remove a certain node on leaf") {
      const int key_to_remove = existing_key_0;
      node_remover remover(key_to_remove);
      tree_visitor_i<int> &visitor = remover;
      visitor.visit(root);

      THEN("it should follow red black tree delete rule one") {
        auto parent = root.load(std::memory_order_acquire);
        REQUIRE(((int)*parent == 7));
        REQUIRE(parent->color() == 1U);

        auto left = parent->get_child(side::left);
        REQUIRE(((int)*left == 3));
        REQUIRE(left->color() == 1U);

        auto right = parent->get_child(side::right);
        REQUIRE(((int)*right == 9));
        REQUIRE(right->color() == 1U);

        auto ll = left->get_child(side::left);
        REQUIRE(((int)*ll == 1));
        REQUIRE(ll->color() == 1U);

        auto llr = ll->get_child(side::right);
        REQUIRE(((int)*llr == 2));
        REQUIRE(llr->color() == 0);

        auto lr = left->get_child(side::right);
        REQUIRE(((int)*lr == 5));
        REQUIRE(lr->color() == 0U);

        auto lrl = lr->get_child(side::left);
        REQUIRE(((int)*lrl == 4));
        REQUIRE(lrl->color() == 1U);

        auto lrr = lr->get_child(side::right);
        REQUIRE(((int)*lrr == 6));
        REQUIRE(lrr->color() == 1U);

        auto rl = right->get_child(side::left);
        REQUIRE(((int)*rl == 8));
        REQUIRE(rl->color() == 1U);

        auto rr = right->get_child(side::right);
        REQUIRE(((int)*rr == 10));
        REQUIRE(rr->color() == 1U);
      }
    }

    AND_WHEN("remove a certain node on branch") {
      const int key_to_remove(existing_key_7);
      node_remover remover(key_to_remove);
      tree_visitor_i<int> &visitor = remover;
      visitor.visit(root);

      THEN("it should follow red black tree delete rule") {
        auto parent = root.load(std::memory_order_acquire);
        REQUIRE(((int)*parent == 3));
        REQUIRE(parent->color() == 1U);

        auto left = parent->get_child(side::left);
        REQUIRE(((int)*left == 1));
        REQUIRE(left->color() == 1U);

        auto right = parent->get_child(side::right);
        REQUIRE(((int)*right == 8));
        REQUIRE(right->color() == 1U);

        auto rl = right->get_child(side::left);
        REQUIRE(((int)*rl == 5));
        REQUIRE(rl->color() == 0U);

        auto rll = rl->get_child(side::left);
        REQUIRE(((int)*rll == 4));
        REQUIRE(rll->color() == 1U);

        auto rlr = rl->get_child(side::right);
        REQUIRE(((int)*rlr == 6));
        REQUIRE(rlr->color() == 1U);

        auto rr = right->get_child(side::right);
        REQUIRE(((int)*rr == 9));
        REQUIRE(rr->color() == 1U);

        auto rrl = rr->get_child(side::left);
        REQUIRE(rrl == nullptr);

        auto rrr = rr->get_child(side::right);
        REQUIRE(((int)*rrr == 10));
        REQUIRE(rrr->color() == 0U);
      }
    }
  }

  GIVEN("a rb-tree with case 2 items setup") {
    auto root = set_up_tree_for_case2();

    WHEN("removing a certain key") {
      const int key_to_remove(existing_key_0);
      node_remover remover(key_to_remove);
      tree_visitor_i<int> &visitor = remover;
      visitor.visit(root);

      THEN("it should follow red black tree delete rule 2") {
        auto parent = root.load(std::memory_order_acquire);
        REQUIRE(((int)*parent == 5));
        REQUIRE(parent->color() == 1U);

        auto left = parent->get_child(side::left);
        REQUIRE(((int)*left == 3));
        REQUIRE(left->color() == 1U);

        auto right = parent->get_child(side::right);
        REQUIRE(((int)*right == 7));
        REQUIRE(right->color() == 1U);

        auto ll = left->get_child(side::left);
        REQUIRE(((int)*ll == 1));
        REQUIRE(ll->color() == 1U);

        auto llr = ll->get_child(side::right);
        REQUIRE(((int)*llr == 2));
        REQUIRE(llr->color() == 0U);

        auto lr = left->get_child(side::right);
        REQUIRE(((int)*lr == 4));
        REQUIRE(lr->color() == 1U);

        auto rl = right->get_child(side::left);
        REQUIRE(((int)*rl == 6));
        REQUIRE(rl->color() == 1U);

        auto rr = right->get_child(side::right);
        REQUIRE(((int)*rr == 8));
        REQUIRE(rr->color() == 1U);
      }
    }

    AND_WHEN("removing an non-existing node") {
      THEN("it will throw") {
        const int key_to_remove(non_existing_key);
        node_remover remover(key_to_remove);
        tree_visitor_i<int> &visitor = remover;
        REQUIRE_THROWS_AS(visitor.visit(root), item_not_exists);
      }
    }
  }

  GIVEN("a rb-tree with case 3 items setup") {
    auto root = set_up_tree_for_case3();

    WHEN("removing an red leaf node") {
      const int key_to_remove(existing_key_7);
      node_remover remover(key_to_remove);
      tree_visitor_i<int> &visitor = remover;
      visitor.visit(root);
      THEN("it should remove it") {
        auto parent = root.load(std::memory_order_acquire);
        REQUIRE(((int)*parent == 5));
        REQUIRE(parent->color() == 1U);

        auto left = parent->get_child(side::left);
        REQUIRE(((int)*left == 3));
        REQUIRE(left->color() == 1U);

        auto right = parent->get_child(side::right);
        REQUIRE(((int)*right == 8));
        REQUIRE(right->color() == 1U);

        auto rl = right->get_child(side::left);
        REQUIRE(rl == nullptr);
      }
    }
  }

  GIVEN("a rb-tree with case 4 items setup") {
    auto root = set_up_tree_for_case4();

    WHEN("removing an red leaf node") {
      const int key_to_remove = existing_key_7;
      node_remover remover(key_to_remove);
      tree_visitor_i<int> &visitor = remover;
      visitor.visit(root);
      THEN("it should remove it") {
        auto parent = root.load(std::memory_order_acquire);
        auto p = (int)*parent;
        INFO("p=" << p );
        REQUIRE((p == 3));
        REQUIRE(parent->color() == 1U);

        auto left = parent->get_child(side::left);
        REQUIRE(((int)*left == 1));
        REQUIRE(left->color() == 1U);

        auto ll = left->get_child(side::left);
        REQUIRE(((int)*ll == 0));
        REQUIRE(ll->color() == 1U);

        auto lr = left->get_child(side::right);
        REQUIRE(((int)*lr == 2));
        REQUIRE(lr->color() == 1U);

        auto right = parent->get_child(side::right);
        REQUIRE(((int)*right == 5));
        REQUIRE(right->color() == 1U);

        auto rl = right->get_child(side::left);
        REQUIRE(((int)*rl == 4));
        REQUIRE(rl->color() == 1U);

        auto rr = right->get_child(side::right);
        REQUIRE(((int)*rr == 8));
        REQUIRE(rr->color() == 1U);

        auto rrl = rr->get_child(side::left);
        REQUIRE(((int)*rrl == 6));
        REQUIRE(rrl->color() == 0U);
      }
    }
  }
}

inline typename rb_node_t::node_handle_t set_up_tree() {
  /*
              4(b)
           /        \
        2(b)        8(r)
       /   \      /      \
     1(b)  3(b)  6(b)    10(b)
    /           /  \     /   \
   0(r)       5(b) 7(b) 9(b) 11(b)
  */

  auto i_0 = std::make_shared<rb_node_t>(existing_key_0);

  auto i_1 = std::make_shared<rb_node_t>(1);
  i_1->increase_color();
  i_1->set_child(i_0, side::left);

  auto i_3 = std::make_shared<rb_node_t>(3);
  i_3->increase_color();

  auto i_2 = std::make_shared<rb_node_t>(2);
  i_2->increase_color();
  i_2->set_child(i_1,side::left);
  i_2->set_child(i_3,side::right);

  auto i_5 = std::make_shared<rb_node_t>(5);
  i_5->increase_color();

  auto i_7 = std::make_shared<rb_node_t>(existing_key_7);
  i_7->increase_color();

  auto i_6 = std::make_shared<rb_node_t>(6);
  i_6->increase_color();
  i_6->set_child(i_5,side::left);
  i_6->set_child(i_7,side::right);

  auto i_9 = std::make_shared<rb_node_t>(9);
  i_9->increase_color();

  auto i_11 = std::make_shared<rb_node_t>(11);
  i_11->increase_color();

  auto i_10 = std::make_shared<rb_node_t>(10);
  i_10->increase_color();
  i_10->set_child(i_9, side::left);
  i_10->set_child(i_11, side::right);

  auto i_8 = std::make_shared<rb_node_t>(8);
  i_8->set_child(i_6, side::left);
  i_8->set_child(i_10, side::right);

  auto i_4 = std::make_shared<rb_node_t>(4);
  i_4->increase_color();
  i_4->set_child(i_2, side::left);
  i_4->set_child(i_8,side::right);

  return i_4;
}

inline typename rb_node_t::node_handle_t set_up_tree_for_case1() {
  /*
              3(b)
           /        \
        1(b)        7(r)
       /   \      /     \
     0(b)  2(b) 5(b)    9(b)
                /  \    /   \
             4(b) 6(b) 8(b) 10(b)
  */

  auto i_0 = std::make_shared<rb_node_t>(existing_key_0);
  i_0->increase_color();

  auto i_2 = std::make_shared<rb_node_t>(2);
  i_2->increase_color();

  auto i_1 = std::make_shared<rb_node_t>(1);
  i_1->increase_color();
  i_1->set_child(i_0, side::left);
  i_1->set_child(i_2, side::right);

  auto i_4 = std::make_shared<rb_node_t>(4);
  i_4->increase_color();
  auto i_6 = std::make_shared<rb_node_t>(6);
  i_6->increase_color();

  auto i_5 = std::make_shared<rb_node_t>(5);
  i_5->increase_color();
  i_5->set_child(i_4, side::left);
  i_5->set_child(i_6, side::right);

  auto i_10 = std::make_shared<rb_node_t>(10);
  i_10->increase_color();

  auto i_8 = std::make_shared<rb_node_t>(8);
  i_8->increase_color();

  auto i_9 = std::make_shared<rb_node_t>(9);
  i_9->increase_color();
  i_9->set_child(i_8, side::left);
  i_9->set_child(i_10, side::right);

  auto i_7 = std::make_shared<rb_node_t>(existing_key_7);
  i_7->set_child(i_5, side::left);
  i_7->set_child(i_9, side::right);

  auto i_3 = std::make_shared<rb_node_t>(3);
  i_3->increase_color();
  i_3->set_child(i_1, side::left);
  i_3->set_child(i_7, side::right);

  return i_3;
}

inline typename rb_node_t::node_handle_t set_up_tree_for_case2() {
  auto i_0 = std::make_shared<rb_node_t>(existing_key_0);
  i_0->increase_color();

  auto i_2 = std::make_shared<rb_node_t>(2);
  i_2->increase_color();

  auto i_1 = std::make_shared<rb_node_t>(1);
  i_1->increase_color();
  i_1->set_child(i_0, side::left);
  i_1->set_child(i_2, side::right);

  auto i_4 = std::make_shared<rb_node_t>(4);
  i_4->increase_color();
  auto i_6 = std::make_shared<rb_node_t>(6);
  i_6->increase_color();

  auto i_5 = std::make_shared<rb_node_t>(5);
  i_5->set_child(i_4, side::left);
  i_5->set_child(i_6, side::right);

  auto i_8 = std::make_shared<rb_node_t>(8);
  i_8->increase_color();

  auto i_7 = std::make_shared<rb_node_t>(existing_key_7);
  i_7->increase_color();
  i_7->set_child(i_5, side::left);
  i_7->set_child(i_8, side::right);

  auto i_3 = std::make_shared<rb_node_t>(3);
  i_3->increase_color();
  i_3->set_child(i_1, side::left);
  i_3->set_child(i_7, side::right);

  return i_3;
}

inline typename rb_node_t::node_handle_t set_up_tree_for_case3() {

  auto i_3 = std::make_shared<rb_node_t>(3);
  i_3->increase_color();

  auto i_7 = std::make_shared<rb_node_t>(existing_key_7);
  auto i_8 = std::make_shared<rb_node_t>(8);
  i_8->increase_color();
  i_8->set_child(i_7, side::left);

  auto i_5 = std::make_shared<rb_node_t>(5);
  i_5->increase_color();
  i_5->set_child(i_3, side::left);
  i_5->set_child(i_8, side::right);

  return i_5;
}

inline typename rb_node_t::node_handle_t set_up_tree_for_case4() {

  auto i_0 = std::make_shared<rb_node_t>(existing_key_0);
  i_0->increase_color();

  auto i_2 = std::make_shared<rb_node_t>(2);
  i_2->increase_color();

  auto i_4 = std::make_shared<rb_node_t>(4);
  i_4->increase_color();

  auto i_3 = std::make_shared<rb_node_t>(3);
  i_3->set_child(i_2, side::left);
  i_3->set_child(i_4, side::right);

  auto i_1 = std::make_shared<rb_node_t>(1);
  i_1->increase_color();
  i_1->set_child(i_0, side::left);
  i_1->set_child(i_3, side::right);

  auto i_6 = std::make_shared<rb_node_t>(6);
  i_6->increase_color();

  auto i_8 = std::make_shared<rb_node_t>(8);
  i_8->increase_color();

  auto i_7 = std::make_shared<rb_node_t>(existing_key_7);
  i_7->increase_color();
  i_7->set_child(i_6, side::left);
  i_7->set_child(i_8, side::right);

  auto i_5 = std::make_shared<rb_node_t>(5);
  i_5->increase_color();
  i_5->set_child(i_1, side::left);
  i_5->set_child(i_7, side::right);

  return i_5;
}

} // namespace btree::algorithm

#endif // TEST