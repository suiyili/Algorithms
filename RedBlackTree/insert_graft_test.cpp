#ifdef TEST

#include <catch2/catch.hpp>
#include "insert_graft.hpp"

namespace bbtree::algorithm {

struct two_level_tree {
  two_level_tree();
  rb_item<int> root;
  rb_item<int> left_child;
  rb_item<int> right_child;
};

struct three_level_tree : public two_level_tree {
  three_level_tree();
  rb_item<int> left_grand_left;
  rb_item<int> left_grand_right;
  rb_item<int> right_grand_left;
  rb_item<int> right_grand_right;
};

static void increase_color(rb_item<int> &item);

SCENARIO("insert graft test", "[insert_graft]") {

  GIVEN("a parent is in children red_status") {
    three_level_tree tree;
    increase_color(tree.root);
    increase_color(tree.left_grand_left);
    increase_color(tree.right_grand_left);

    auto root_ptr = &tree.root;
    item_handle root(root_ptr);

    CHECK(root->red_status() == item_status::children);

    WHEN("do graft on a child") {
      item_handle<int> child(root->left);     
      insert_graft(root, child);

      THEN("it should push down color") { REQUIRE(root->color() == 0U); }
    }
  }

  GIVEN("a parent is in lchild red_status and left child has rchild red_status") {
    three_level_tree tree;

    increase_color(tree.root);
    increase_color(tree.right_child);
    increase_color(tree.left_grand_left);

    auto root_ptr = &tree.root;
    item_handle root(root_ptr);    

    CHECK(root->red_status() == item_status::lchild);
    CHECK(root->left->red_status() == item_status::rchild);

    WHEN("parent does graft") {
      item_handle<int> child(root->left);
      insert_graft(root, child);
            
      THEN("it should make new root with left grand right") {
        REQUIRE(&*root == &tree.left_grand_right);
        REQUIRE(root->color() == 1U);
      }

      AND_THEN("it should make new right with root") {
        auto right_ptr = root->right;
        REQUIRE(right_ptr == &tree.root);
        REQUIRE(right_ptr->color() == 0U);       
      }

      AND_THEN("it should keep the left child") {
        auto left_ptr = root->left;
        REQUIRE(left_ptr == &tree.left_child);
        REQUIRE(left_ptr->color() == 0U);
      }
    }
  }

  GIVEN("parent is lchild red_status and left child has left red_status") {
    three_level_tree tree;
    increase_color(tree.root);
    increase_color(tree.right_child);
    increase_color(tree.left_grand_right);

    auto root_ptr = &tree.root;
    item_handle root(root_ptr);

    CHECK(root->red_status() == item_status::lchild);
    CHECK(root->left->red_status() == item_status::lchild);

    WHEN("parent does graft") {
      item_handle<int> child(root->left);
      insert_graft(root, child);
      
      THEN("it should make new root with left child") {
        REQUIRE(&*root == &tree.left_child);
        REQUIRE(root->color() == 1U);
        
      }
      AND_THEN("it should make new right child to old root") {
        auto right_ptr = root->right;
        REQUIRE(right_ptr == &tree.root);
        REQUIRE(right_ptr->color() == 0U);
      }
      AND_THEN("it should make new left to old left grand left") {
        auto left_ptr = root->left;
        REQUIRE(left_ptr == &tree.left_grand_left);
        REQUIRE(left_ptr->color() == 0U);
      }
    }
  }

  GIVEN("parent is rchild red_status and right child has lchild red_status") {
    three_level_tree tree;
    increase_color(tree.root);
    increase_color(tree.left_child);
    increase_color(tree.right_grand_right);

    auto root_ptr = &tree.root;
    item_handle root(root_ptr);

    CHECK(root->red_status() == item_status::rchild);
    CHECK(root->right->red_status() == item_status::lchild);

    WHEN("parent does graft") {
      item_handle<int> child(root->right);
      insert_graft(root, child);

      THEN("it should make new root with right grand left") {
        REQUIRE(&*root == &tree.right_grand_left);
        REQUIRE(root->color() == 1U);
      }

      AND_THEN("it should make new left with root") {
        auto left_ptr = root->left;
        REQUIRE(left_ptr == &tree.root);
        REQUIRE(left_ptr->color() == 0U);
      }

      AND_THEN("it should keep the right child") {
        auto right_ptr = root->right;
        REQUIRE(right_ptr == &tree.right_child);
        REQUIRE(right_ptr->color() == 0U);
      }
    }
  }

  GIVEN("parent is rchild red_status and right child has rchild red_status") {
    three_level_tree tree;
    increase_color(tree.root);
    increase_color(tree.left_child);
    increase_color(tree.right_grand_left);

    auto root_ptr = &tree.root;
    item_handle root(root_ptr);

    CHECK(root->red_status() == item_status::rchild);
    CHECK(root->right->red_status() == item_status::rchild);

    WHEN("parent does graft") {
        
      item_handle<int> child(root->right);
      insert_graft(root, child);

      THEN("it should make new root with right child") {
        REQUIRE(&*root == &tree.right_child);
        REQUIRE(root->color() == 1U);
      }
      AND_THEN("it should make new left child to old root") {
        auto left_ptr = root->left;
        REQUIRE(left_ptr == &tree.root);
        REQUIRE(left_ptr->color() == 0U);
      }
      AND_THEN("it should make new right to old right grand right") {
        auto right_ptr = root->right;
        REQUIRE(right_ptr == &tree.right_grand_right);
        REQUIRE(right_ptr->color() == 0U);
      }
    }
  }
}

two_level_tree::two_level_tree()
    : root(std::make_unique<int>(4)), left_child(std::make_unique<int>(2)),
      right_child(std::make_unique<int>(6)) {
  root.left = &left_child;
  root.right = &right_child;

  left_child.left = left_child.right = right_child.left = right_child.right =
      nullptr;
}

three_level_tree::three_level_tree()
    : left_grand_left(std::make_unique<int>(1)),
      left_grand_right(std::make_unique<int>(3)),
      right_grand_left(std::make_unique<int>(5)),
      right_grand_right(std::make_unique<int>(7)) {
  left_child.left = &left_grand_left;
  left_child.right = &left_grand_right;
  right_child.left = &right_grand_left;
  right_child.right = &right_grand_right;

  left_grand_left.left = left_grand_left.right = left_grand_right.left =
      left_grand_right.right = right_grand_left.left = right_grand_left.right =
          right_grand_right.left = right_grand_right.right = nullptr;
}

inline void increase_color(rb_item<int> &item) {
  auto left = item.left;
  auto right = item.right;
  item.left = nullptr;
  item.right = nullptr;
  item.increase_color();
  item.left = left;
  item.right = right;
}

} // namespace bbtree::algorithm

#endif // TEST