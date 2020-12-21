#ifdef TEST

#include <catch2/catch.hpp>
#include "item_not_exists.hpp"
#include "item_remover.hpp"

namespace bbtree::algorithm {

const int existing_key_0 = 0, existing_key_7 = 7, existing_key_9 = 9, non_existing_key = -1;

static rb_item<int> *set_up_tree_for_case1();
static rb_item<int> *set_up_tree_for_case2();
static rb_item<int> *set_up_tree_for_case3();
static rb_item<int> *set_up_tree_for_case4();

SCENARIO("item remover test", "[item_remover]") {
  GIVEN("a rb-tree with case 1 items setup") {
    auto root = set_up_tree_for_case1();
    item_handle root_handle(root);

    WHEN("remove a certain item on leaf") {
      const int key_to_remove = existing_key_0;
      item_remover remover(key_to_remove);
      tree_visitor_i<int> &visitor = remover;
      visitor.visit(root_handle);

      THEN("it should follow red black tree delete rule one") {

        REQUIRE(root->get_key() == 7);
        REQUIRE(root->color() == 1U);

        auto left = root->left;
        REQUIRE(left->get_key() == 3);
        REQUIRE(left->color() == 1U);

        auto right = root->right;
        REQUIRE(right->get_key() == 9);
        REQUIRE(right->color() == 1U);

        auto ll = left->left;
        REQUIRE(ll->get_key() == 1);
        REQUIRE(ll->color() == 1U);

        auto llr = ll->right;
        REQUIRE(llr->get_key() == 2);
        REQUIRE(llr->color() == 0);

        auto lr = left->right;
        REQUIRE(lr->get_key() == 5);
        REQUIRE(lr->color() == 0U);

        auto lrl = lr->left;
        REQUIRE(lrl->get_key() == 4);
        REQUIRE(lrl->color() == 1U);

        auto lrr = lr->right;
        REQUIRE(lrr->get_key() == 6);
        REQUIRE(lrr->color() == 1U);

        auto rl = right->left;
        REQUIRE(rl->get_key() == 8);
        REQUIRE(rl->color() == 1U);

        auto rr = right->right;
        REQUIRE(rr->get_key() == 10);
        REQUIRE(rr->color() == 1U);
      }
    }

    AND_WHEN("remove a certain item on branch") {
      const int key_to_remove(existing_key_7);
      item_remover remover(key_to_remove);
      tree_visitor_i<int> &visitor = remover;
      visitor.visit(root_handle);

      THEN("it should follow red black tree delete rule") {

        REQUIRE(root->get_key() == 3);
        REQUIRE(root->color() == 1U);

        auto left = root->left;
        REQUIRE(left->get_key() == 1);
        REQUIRE(left->color() == 1U);

        auto right = root->right;
        REQUIRE(right->get_key() == 8);
        REQUIRE(right->color() == 1U);

        auto rl = right->left;
        REQUIRE(rl->get_key() == 5);
        REQUIRE(rl->color() == 0U);

        auto rll = rl->left;
        REQUIRE(rll->get_key() == 4);
        REQUIRE(rll->color() == 1U);

        auto rlr = rl->right;
        REQUIRE(rlr->get_key() == 6);
        REQUIRE(rlr->color() == 1U);

        auto rr = right->right;
        REQUIRE(rr->get_key() == 9);
        REQUIRE(rr->color() == 1U);

        auto rrl = rr->left;
        REQUIRE(rrl == nullptr);

        auto rrr = rr->right;
        REQUIRE(rrr->get_key() == 10);
        REQUIRE(rrr->color() == 0U);
      }
    }
  }

  GIVEN("a rb-tree with case 2 items setup") {
    auto root = set_up_tree_for_case2();
    item_handle root_handle(root);

    WHEN("removing a certain key") {
      const int key_to_remove(existing_key_0);
      item_remover remover(key_to_remove);
      tree_visitor_i<int> &visitor = remover;
      visitor.visit(root_handle);

      THEN("it should follow red black tree delete rule 2") {

        REQUIRE(root->get_key() == 5);
        REQUIRE(root->color() == 1U);

        auto left = root->left;
        REQUIRE(left->get_key() == 3);
        REQUIRE(left->color() == 1U);

        auto right = root->right;
        REQUIRE(right->get_key() == 7);
        REQUIRE(right->color() == 1U);

        auto ll = left->left;
        REQUIRE(ll->get_key() == 1);
        REQUIRE(ll->color() == 1U);

        auto llr = ll->right;
        REQUIRE(llr->get_key() == 2);
        REQUIRE(llr->color() == 0U);

        auto lr = left->right;
        REQUIRE(lr->get_key() == 4);
        REQUIRE(lr->color() == 1U);

        auto rl = right->left;
        REQUIRE(rl->get_key() == 6);
        REQUIRE(rl->color() == 1U);

        auto rr = right->right;
        REQUIRE(rr->get_key() == 8);
        REQUIRE(rr->color() == 1U);
      }
    }

    AND_WHEN("removing an non-existing item") {
      THEN("it will throw") {
        const int key_to_remove(non_existing_key);
        item_remover remover(key_to_remove);
        tree_visitor_i<int> &visitor = remover;
        REQUIRE_THROWS_AS(visitor.visit(root_handle), item_not_exists);
      }
    }
  }

  GIVEN("a rb-tree with case 3 items setup") {
    auto root = set_up_tree_for_case3();
    item_handle root_handle(root);

    WHEN("removing an red leaf item") {
      const int key_to_remove(existing_key_7);
      item_remover remover(key_to_remove);
      tree_visitor_i<int> &visitor = remover;
      visitor.visit(root_handle);
      THEN("it should remove it") {

        REQUIRE(root->get_key() == 5);
        REQUIRE(root->color() == 1U);

        auto left = root->left;
        REQUIRE(left->get_key() == 3);
        REQUIRE(left->color() == 1U);

        auto right = root->right;
        REQUIRE(right->get_key() == 8);
        REQUIRE(right->color() == 1U);

        auto rl = right->left;
        REQUIRE(rl == nullptr);
      }
    }
  }

  GIVEN("a rb-tree with case 4 items setup") {
    auto root = set_up_tree_for_case4();
    item_handle root_handle(root);

    WHEN("removing an red leaf item") {
      const int key_to_remove = existing_key_7;
      item_remover remover(key_to_remove);
      tree_visitor_i<int> &visitor = remover;
      visitor.visit(root_handle);
      THEN("it should remove it") {

        REQUIRE(root->get_key() == 3);
        REQUIRE(root->color() == 1U);

        auto left = root->left;
        REQUIRE(left->get_key() == 1);
        REQUIRE(left->color() == 1U);

        auto ll = left->left;
        REQUIRE(ll->get_key() == 0);
        REQUIRE(ll->color() == 1U);

        auto lr = left->right;
        REQUIRE(lr->get_key() == 2);
        REQUIRE(lr->color() == 1U);

        auto right = root->right;
        REQUIRE(right->get_key() == 5);
        REQUIRE(right->color() == 1U);

        auto rl = right->left;
        REQUIRE(rl->get_key() == 4);
        REQUIRE(rl->color() == 1U);

        auto rr = right->right;
        REQUIRE(rr->get_key() == 8);
        REQUIRE(rr->color() == 1U);

        auto rrl = rr->left;
        REQUIRE(rrl->get_key() == 6);
        REQUIRE(rrl->color() == 0U);
      }
    }
  }
}

inline rb_item<int> *set_up_tree_for_case1() {
  auto i_0 = new rb_item(std::make_unique<int>(existing_key_0));
  i_0->increase_color();

  auto i_2 = new rb_item(std::make_unique<int>(2));
  i_2->increase_color();

  auto i_1 = new rb_item(std::make_unique<int>(1));
  i_1->increase_color();
  i_1->left = i_0;
  i_1->right = i_2;

  auto i_4 = new rb_item(std::make_unique<int>(4));
  i_4->increase_color();
  auto i_6 = new rb_item(std::make_unique<int>(6));
  i_6->increase_color();

  auto i_5 = new rb_item(std::make_unique<int>(5));
  i_5->increase_color();
  i_5->left = i_4;
  i_5->right = i_6;

  auto i_10 = new rb_item(std::make_unique<int>(10));
  i_10->increase_color();

  auto i_8 = new rb_item(std::make_unique<int>(8));
  i_8->increase_color();

  auto i_9 = new rb_item(std::make_unique<int>(9));
  i_9->increase_color();
  i_9->left = i_8;
  i_9->right = i_10;

  auto i_7 = new rb_item(std::make_unique<int>(existing_key_7));
  i_7->left = i_5;
  i_7->right = i_9;

  auto i_3 = new rb_item(std::make_unique<int>(3));
  i_3->increase_color();
  i_3->left = i_1;
  i_3->right = i_7;

  return i_3;
}

inline rb_item<int> *set_up_tree_for_case2() {
  auto i_0 = new rb_item(std::make_unique<int>(existing_key_0));
  i_0->increase_color();

  auto i_2 = new rb_item(std::make_unique<int>(2));
  i_2->increase_color();

  auto i_1 = new rb_item(std::make_unique<int>(1));
  i_1->increase_color();
  i_1->left = i_0;
  i_1->right = i_2;

  auto i_4 = new rb_item(std::make_unique<int>(4));
  i_4->increase_color();
  auto i_6 = new rb_item(std::make_unique<int>(6));
  i_6->increase_color();

  auto i_5 = new rb_item(std::make_unique<int>(5));
  i_5->left = i_4;
  i_5->right = i_6;

  auto i_8 = new rb_item(std::make_unique<int>(8));
  i_8->increase_color();

  auto i_7 = new rb_item(std::make_unique<int>(existing_key_7));
  i_7->increase_color();
  i_7->left = i_5;
  i_7->right = i_8;

  auto i_3 = new rb_item(std::make_unique<int>(3));
  i_3->increase_color();
  i_3->left = i_1;
  i_3->right = i_7;

  return i_3;
}

inline rb_item<int> *set_up_tree_for_case3() {

  auto i_3 = new rb_item(std::make_unique<int>(3));
  i_3->increase_color();

  auto i_7 = new rb_item(std::make_unique<int>(existing_key_7));
  auto i_8 = new rb_item(std::make_unique<int>(8));
  i_8->increase_color();
  i_8->left = i_7;

  auto i_5 = new rb_item(std::make_unique<int>(5));
  i_5->increase_color();
  i_5->left = i_3;
  i_5->right = i_8;

  return i_5;
}

rb_item<int> *set_up_tree_for_case4() {

  auto i_0 = new rb_item(std::make_unique<int>(existing_key_0));
  i_0->increase_color();

  auto i_2 = new rb_item(std::make_unique<int>(2));
  i_2->increase_color();
  
  auto i_4 = new rb_item(std::make_unique<int>(4));
  i_4->increase_color();
  
  auto i_3 = new rb_item(std::make_unique<int>(3));
  i_3->left = i_2;
  i_3->right = i_4;  

  auto i_1 = new rb_item(std::make_unique<int>(1));
  i_1->increase_color();
  i_1->left = i_0;
  i_1->right = i_3;

  
  auto i_6 = new rb_item(std::make_unique<int>(6));
  i_6->increase_color();

  auto i_8 = new rb_item(std::make_unique<int>(8));
  i_8->increase_color();

  auto i_7 = new rb_item(std::make_unique<int>(existing_key_7));
  i_7->increase_color();
  i_7->left = i_6;
  i_7->right = i_8;

  auto i_5 = new rb_item(std::make_unique<int>(5));
  i_5->increase_color();
  i_5->left = i_1;
  i_5->right = i_7;  

  return i_5;
}

} // namespace bbtree::algorithm

#endif // TEST