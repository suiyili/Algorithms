#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include <algorithm/node_inserter/node_inserter.hpp>
#include <algorithm/node_remover/node_remover.hpp>
#include <rb_tree/rb_tree.hpp>
#include <thread>
#include <atomic>
#include <exception>
#include <ranges>

using namespace btree::node;
using namespace btree::algorithm;

namespace btree {

using node_inserter_t = node_inserter<int>;
using node_remover_t = node_remover<int>;

SCENARIO("red black tree test", "[rb_tree]") {
  GIVEN("a number of items inserted") {
    const int key_exists = 9, non_existing_key = 32;

    rb_tree<int> tree;
    std::vector<node_inserter_t> inserters;
    inserters.reserve(10);
    inserters.emplace_back(-2);
    inserters.emplace_back(key_exists);
    inserters.emplace_back(8);
    inserters.emplace_back(15);
    inserters.emplace_back(6);
    inserters.emplace_back(33);

    for (auto &i : inserters)
      tree.accept(i);

    WHEN("search the given key") {
      auto found = tree.contains(key_exists);
      THEN("it should be found") { REQUIRE(found); }
    }

    AND_WHEN("search a non-exsiting key") {
      THEN("it should return false") {
        REQUIRE_FALSE(tree.contains(non_existing_key));
      }
    }

    AND_WHEN("insert an existing key") {
      THEN("it will throw") {
        node_inserter_t insert_existing(key_exists);
        REQUIRE_THROWS_AS(tree.accept(insert_existing), item_already_exists);
      }
    }

    AND_WHEN("remove an existing key") {
      const int to_remove(key_exists);
      node_remover remove_existing(to_remove);
      
      tree.accept(remove_existing);

      THEN("the key should be removed from the tree") {
        REQUIRE_FALSE(tree.contains(key_exists));
      }
    }

    AND_WHEN("remove non-existing key") {
      const int to_remove(non_existing_key);

      THEN("it will throw") {
        node_remover remove_existing(to_remove);
        REQUIRE_THROWS_AS(tree.accept(remove_existing), item_not_exists);
      }
    }
  }
  GIVEN("a red black tree") {
    rb_tree<int> tree;

    std::vector<node_inserter_t> inserters;
    inserters.reserve(10);
    inserters.emplace_back(-2);
    inserters.emplace_back(9);
    inserters.emplace_back(8);
    inserters.emplace_back(15);
    inserters.emplace_back(6);
    inserters.emplace_back(33);

    std::vector<node_remover_t> removers;
    removers.reserve(10);
    removers.emplace_back(6);
    removers.emplace_back(33);
    removers.emplace_back(9);
    removers.emplace_back(8);
    removers.emplace_back(-2);
    removers.emplace_back(15);

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
          for (auto &i : inserters)
            tree.accept(i);
          for (auto &i : removers)
            tree.accept(i);
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