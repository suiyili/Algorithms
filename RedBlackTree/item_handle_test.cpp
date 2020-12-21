#ifdef TEST

#include <catch2/catch.hpp>
#include "item_handle.hpp"
#include "item_not_exists.hpp"
#include "rotate_error.hpp"

namespace bbtree::item {

SCENARIO("item handle test", "[item_handle]") {

  GIVEN("a rb item") {
    rb_item item(std::make_unique<int>(5));
    auto item_ptr = &item;
    item_handle handle(item_ptr);

    CHECK(handle);

    WHEN("set new item ptr") {
      auto old = handle.set(nullptr);
      THEN("it should return old one") { REQUIRE(old == &item); }

      AND_THEN("it should hold the new one") {
        REQUIRE_FALSE((bool)handle);
      }
    }

    AND_WHEN("release the item ptr") {
      THEN("it should release the ptr") { REQUIRE(handle.release() == &item); }
    }
  }

  GIVEN("a null rb item") {
    rb_item<int> *item = nullptr;
    item_handle handle(item);

    CHECK_FALSE(handle);
    WHEN("use the item of the ptr") {
      THEN("it will throw item_not_exists") {
        REQUIRE_THROWS_AS(handle->color(), item_not_exists);
      }

      AND_THEN("it will throw item_not_exists") {
        REQUIRE_THROWS_AS((*handle).color(), item_not_exists);
      }
    }

    AND_WHEN("rotate") {
      THEN("it will throw item_not_exists") {
        REQUIRE_THROWS_AS(handle.rotate(), item_not_exists);
      }
    }
  }

  GIVEN("a valid item handle") {
    rb_item item_1(std::make_unique<int>(5));
    auto item_ptr = &item_1;
    item_handle handle(item_ptr);

    WHEN("set ptr of the item") {
      rb_item item_2(std::make_unique<int>(5));
      handle.set(&item_2);
      THEN("it should asign new ptr to the ref") {
        REQUIRE(&*handle == &item_2);
        REQUIRE(item_ptr == &item_2);
      }
    }
  }

  GIVEN("a red parent and two black children") {
    rb_item parent(std::make_unique<int>(5));
    auto top = &parent;

    rb_item left_child(std::make_unique<int>(4));
    left_child.increase_color();
    parent.left = &left_child;
    rb_item right_child(std::make_unique<int>(6));
    right_child.increase_color();
    parent.right = &right_child;

    CHECK(parent.red_status() == item_status::parent);

    WHEN("rotate") {
      item_handle handle(top);
      THEN("it should throw") {
        REQUIRE_THROWS_AS(handle.rotate(), rotate_error);
      }
    }
  }

  GIVEN("an item without children") {
    rb_item item(std::make_unique<int>(5));
    item.increase_color();
    auto top = &item;

    CHECK(item.red_status() == item_status::none);

    WHEN("rotate") {
      item_handle handle(top);
      THEN("it should throw") {
        REQUIRE_THROWS_AS(handle.rotate(), rotate_error);
      }
    }
  }

  GIVEN("a black parent with two black children") {
    rb_item parent(std::make_unique<int>(5));
    parent.increase_color();

    rb_item left_child(std::make_unique<int>(4));
    left_child.increase_color();
    parent.left = &left_child;
    rb_item right_child(std::make_unique<int>(6));
    right_child.increase_color();
    parent.right = &right_child;

    auto top = &parent;

    CHECK(parent.red_status() == item_status::none);

    WHEN("rotate") {
      item_handle handle(top);
      THEN("it should throw") {
        REQUIRE_THROWS_AS(handle.rotate(), rotate_error);
      }
    }
  }

  GIVEN("a black parent with two red children") {
    rb_item parent(std::make_unique<int>(5));
    parent.increase_color();

    rb_item left_child(std::make_unique<int>(4));
    parent.left = &left_child;
    rb_item right_child(std::make_unique<int>(6));
    parent.right = &right_child;

    auto top = &parent;

    CHECK(parent.red_status() == item_status::children);

    WHEN("rotate") {
      item_handle handle(top);
      THEN("it should throw") {
        REQUIRE_THROWS_AS(handle.rotate(), rotate_error);
      }
    }
  }

  GIVEN("a black parent with left child as only red child") {
    rb_item parent(std::make_unique<int>(5));
    parent.increase_color();
    parent.increase_color();
    auto parent_color = parent.color();

    rb_item left_child(std::make_unique<int>(4));
    parent.left = &left_child;

    auto top = &parent;

    CHECK(parent.red_status() == item_status::lchild);
    CHECK(left_child.color() == 0);

    WHEN("rotate") {
      item_handle handle(top);
      handle.rotate();
      THEN("it should exchange color between left child and parent") {
        REQUIRE(parent.color() == 0U);
        REQUIRE(left_child.color() == parent_color);
      }
    }
  }

  GIVEN("a red parent with right child as only red child") {
    rb_item parent(std::make_unique<int>(5));
    auto top = &parent;

    rb_item left_child(std::make_unique<int>(4));
    left_child.increase_color();
    parent.left = &left_child;

    rb_item right_child(std::make_unique<int>(6));
    parent.right = &right_child;

    CHECK(parent.red_status() == item_status::rchild);
    CHECK(parent.color() == 0);

    AND_WHEN("rotate") {
      item_handle handle(top);
      handle.rotate();
      THEN("it should exchange color between right child and parent") {
        REQUIRE(parent.color() == 0U);
        REQUIRE(right_child.color() == 0U);
      }
    }
  }
}

} // namespace bbtree::item

#endif // TEST