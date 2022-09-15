#ifdef TEST

#include "priority_queue.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <array>
#include <vector>

using namespace Catch::Matchers;

namespace graph::generic {

SCENARIO("priority queue test", "[priority_queue]") {
  GIVEN("a bench of number"){
    std::array<int, 8> numbers{9, 8, 2, -4, -3, 0, -10, 12};
    WHEN("pushed them into a ascent priority queue") {
      priority_queue<decltype(numbers)::value_type> queue;
      for(auto& i : numbers)
        queue.push(&i);
      THEN("the queue should pop numbers ascently") {
        std::vector<int> expected{ -10, -4, -3, 0, 2, 8, 9, 12 };
        decltype(expected) actual;
        while (auto i = queue.pop())
          actual.push_back(*i);
        REQUIRE_THAT(actual, Equals(expected));
      }
      AND_WHEN("swim one of number") {
        numbers[1] = -1; // change 8 to -1
        queue.update(&(numbers[1]));
        THEN("the queue should pop new ascent numbers")
        {
          std::vector<int> expected{ -10, -4, -3, -1, 0, 2, 9, 12 };
          decltype(expected) actual;
          while (auto i = queue.pop())
            actual.push_back(*i);
          REQUIRE_THAT(actual, Equals(expected));
        }
      }
      AND_WHEN("sink one of number")
      {
        numbers[3] = 1; // change -4 to 1
        queue.update(&(numbers[1]));
        THEN("the queue should pop new ascent numbers")
        {
          std::vector<int> expected{ -10, -3, 0, 1, 2, 8, 9, 12 };
          decltype(expected) actual;
          while (auto i = queue.pop())
            actual.push_back(*i);
          REQUIRE_THAT(actual, Equals(expected));
        }
      }

    }
  }  
}

} // namespace graph::generic

#endif // TEST