#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include <rb_tree/rb_tree.hpp>
#include <thread>
#include <atomic>
#include <exception>
#include <ranges>

using namespace btree::node;
using namespace btree::algo;

namespace btree {

SCENARIO("red black tree test", "[rb_tree]") {
  GIVEN("a number of items inserted") {
    const int key_exists = 9, non_existing_key = 32;

    rb_tree<int> tree;
    for(int i : {-2, key_exists, 8, 15, 6, 33})
      tree.insert(i);

    WHEN("search the given key") {
      auto found = tree.contains(key_exists);
      THEN("it should be found") { REQUIRE(found); }
    }

    AND_WHEN("search a non-existing key") {
      THEN("it should return false") {
        REQUIRE_FALSE(tree.contains(non_existing_key));
      }
    }

    AND_WHEN("insert an existing key") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(tree.insert(key_exists), item_already_exists);
      }
    }

    AND_WHEN("remove an existing key") {
      const int to_remove(key_exists);
      tree.remove(to_remove);

      THEN("the key should be removed from the tree") {
        REQUIRE_FALSE(tree.contains(key_exists));
      }
    }

    AND_WHEN("remove non-existing key") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(tree.remove(non_existing_key), item_not_exists);
      }
    }
  }
  GIVEN("a red black tree") {
    rb_tree<int> tree;

    int keys_to_insert[] = {-2, 9, 8, 15, 6, 33};

    int keys_to_remove[] = {6, 33, 9, 8, -2, 15};

    WHEN("multi-threads read/search and single thread write (insert/remove) to the tree"){

      std::exception_ptr read1_ex, read2_ex, write_ex;
      CHECK((!read1_ex && !read2_ex && !write_ex));

      std::atomic_flag signal;
      std::jthread th1([&]{
        signal.wait(true);
        try{
          while(signal.test()) {
            tree.contains(5);
            tree.contains(6);
            tree.contains(33);
            tree.contains(-2);
            tree.contains(9);
            tree.contains(24);
          }
        } catch (...){
          read1_ex = std::current_exception();
          INFO("reading error");
        }
      });

      std::jthread th2([&]{
        signal.wait(true);
        try{
          while(signal.test()) {
            tree.contains(52);
            tree.contains(6);
            tree.contains(3);
            tree.contains(2);
            tree.contains(9);
            tree.contains(8);
          }
        } catch (...){
          read2_ex = std::current_exception();
          INFO("reading error");
        }
      });

      signal.notify_all();
      try{
        for(auto _ : std::views::iota(0, 100)) {
          for (auto &i : keys_to_insert)
            tree.insert(i);
          for (auto &i : keys_to_remove)
            tree.remove(i);
        }
      } catch (const std::exception& ex) {
        write_ex = std::current_exception();
        UNSCOPED_INFO("writing error: " << ex.what());
      }
      signal.clear();

      REQUIRE((!read1_ex && !read2_ex && !write_ex));
    }
  }
}
} // namespace btree

#endif // TEST