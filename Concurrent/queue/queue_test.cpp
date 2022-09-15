#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include "queue.hpp"
#include <chrono>
#include <future>
#include <thread>
#include <vector>

using namespace Catch::Matchers;

namespace concurrent {

using namespace Catch;
using int_queue = queue<int>;
void push(int_queue &queue, const std::vector<int> &jobs);
std::vector<int> pop(int_queue &queue, size_t count);

SCENARIO("concurrent queue test", "[concurrent_queue]") {

  GIVEN("an empty queue") {
    int_queue queue(5);

    WHEN("input null object") {
      auto inserted = queue.push(nullptr);
      THEN("it should fail") { REQUIRE_FALSE(inserted); }
    }

    WHEN("get item") {
      std::unique_ptr<int> output;
      auto popped = queue.pop(output);
      THEN("it will block next input") { REQUIRE_FALSE(popped); }
    }
  }

  GIVEN("a queue which is full") {
    int_queue queue(2);
    const std::vector<int> expected_items{1, 2};
    push(queue, expected_items);

    WHEN("push one more") {
      auto pushed = queue.push(std::make_unique<int>(3));
      THEN("it will block next input") { REQUIRE_FALSE(pushed); }
    }
  }

  /*non functional queue*/
  GIVEN("a queue with multi-threads for input and output") {
    int_queue queue(5);

    WHEN("input with two ends two threads") {
      const std::vector<int> expected_items{1, 2, 3, 4, 5, 6};
      std::vector<int> actual_sequence;
      actual_sequence.reserve(expected_items.size());
      auto pushing = std::async(std::launch::async,
                                [&]() { push(queue, expected_items); });
      auto popping = std::async(std::launch::async, [&]() {
        actual_sequence = pop(queue, expected_items.size());
      });

      queue.wait_until_empty();

      pushing.wait();
      popping.wait();

      THEN("should output all items in sequence") {
        REQUIRE_THAT(actual_sequence, Contains(expected_items));
      }
    }

    WHEN("multi-thread for both input and output") {
      const size_t input_count = 1000;
      std::atomic<size_t> output_count(0);
      std::thread input_threads[2]{std::thread([&]() {
                                     const std::vector<int> input(400, 1);
                                     push(queue, input);
                                   }),
                                   std::thread([&]() {
                                     const std::vector<int> input(
                                         input_count - 400, 1);
                                     push(queue, input);
                                   })};

      std::thread output_threads[2]{
          std::thread(
              [&]() { output_count.fetch_add(pop(queue, 600).size()); }),
          std::thread([&]() {
            output_count.fetch_add(pop(queue, input_count - 600).size());
          })};

      queue.wait_until_empty();

      for (auto &th : input_threads)
        th.join();
      for (auto &th : output_threads)
        th.join();

      THEN("should have same output count as ") {
        REQUIRE((size_t)output_count == input_count);
      }
    }
  }
}

inline void push(int_queue &queue, const std::vector<int> &jobs) {
  for (auto &job : jobs) {
    while (!queue.push(std::make_unique<int>(job)))
      ;
  }
}

inline std::vector<int> pop(int_queue &queue, size_t count) {
  std::vector<int> out_items;
  out_items.reserve(count);
  std::unique_ptr<int> output;
  for (size_t i = 0; i < count; ++i) {
    while (!queue.pop(output))
      ;
    out_items.push_back(*output);
  }
  return move(out_items);
}

} // namespace concurrent

#endif // TEST