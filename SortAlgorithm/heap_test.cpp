#ifdef TEST
#include <catch2/catch.hpp>
#include "heap.hpp"
#include <array>
#include <stdexcept>
#include <vector>

namespace sortalgo::heapsort {

SCENARIO("heap test", "[heap_sorter]") {

  GIVEN("empty input") {
    std::vector<int> inputs{1, 2};
    auto comp = [](const int &left, const int &right) { return left < right; };
    auto begin = inputs.begin(), end = begin;
    WHEN("construct heap") {
      auto ctor = [&] { heap h(begin, end, comp); };
      THEN("it should throw") {
        REQUIRE_THROWS_AS(ctor(), std::invalid_argument);
      }
    }
  }

  GIVEN("an six elements array") {
    std::vector<int> source{24, -15, -2, 8, -21, 33};
    auto comp = [](const int &left, const int &right) { return left < right; };

    WHEN("construct heap") {

      heap array_heap(source.begin(), source.end(), comp);

      THEN("it should be re-arranged in-place by heap algo") {
        std::vector<int> expected{33, 8, 24, -15, -21, -2};
        REQUIRE_THAT(source, Catch::Equals(expected));
      }
    }
  }

  GIVEN("a heap built with one elements array") {
    std::vector<int> source{24};
    auto comp = [](const int &left, const int &right) { return left < right; };
    heap array_heap(source.begin(), source.end(), comp);

    WHEN("it pop up the top element") {
      auto pop = array_heap.pop_top();

      THEN("the top one is the one item in the array") {
        auto last = source.begin();
        REQUIRE(pop == last);
      }
      AND_THEN("the top one has the same value of the only item") {
        REQUIRE(*pop == source[0]);
      }
      AND_THEN("the size of the heap no change") {
        REQUIRE(source.size() == array_heap.size());
      }
    }
  }

  GIVEN("a heap built with two elements array") {
    std::vector<int> source{33, 8, 24, -15, -21, -2};
    auto comp = [](const int &left, const int &right) { return left < right; };
    heap array_heap(source.begin(), source.end(), comp);

    WHEN("it pop up the top element") {
      auto pop = array_heap.pop_top();

      THEN("the top one is in the last index of the array") {
        auto last = source.end() - 1;
        REQUIRE(pop == last);
      }
      AND_THEN("the top one has the max value") { REQUIRE(*pop == 33); }
      AND_THEN("the size of the heap decrease one") {
        auto size = source.size() - 1;
        REQUIRE(size == array_heap.size());
      }
    }
    AND_WHEN("it pop up twice") {
      auto pop = array_heap.pop_top();
      pop = array_heap.pop_top();
      THEN("the top one is in the last index of the array") {
        auto last = source.end() - 2;
        REQUIRE(pop == last);
      }
      AND_THEN("the top one has the max value") { REQUIRE(*pop == 24); }
      AND_THEN("the size of the heap decrease one") {
        auto size = source.size() - 2;
        REQUIRE(size == array_heap.size());
      }
    }
  }
}

} // namespace sortalgo::heapsort

#endif // TEST
