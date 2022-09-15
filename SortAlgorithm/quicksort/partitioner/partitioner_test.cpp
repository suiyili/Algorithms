#ifdef TEST
#include <catch2/catch_test_macros.hpp>
#include "partitioner.hpp"
#include <array>

namespace sort_algo {

SCENARIO("partitioner test", "[partitioner]") {

  GIVEN("empty input") {
    std::array<int, 2> inputs{1, 2};
    auto comp = [](const int &left, const int &right) { return left < right; };
    auto begin = inputs.begin(), end = begin;
    WHEN("construct heap") {
      auto ctor = [&] { partitioner p(begin, end, comp); };
      THEN("it should throw") {
        REQUIRE_THROWS_AS(ctor(), std::invalid_argument);
      }
    }
  }

  GIVEN("single element input partitioner") {
    std::array<int, 1> inputs{1};
    auto comp = [](const int &left, const int &right) { return left < right; };
    partitioner partition(inputs.begin(), inputs.end(), comp);
    WHEN("get front") {
      auto front = partition.get_front();
      THEN("it should be begin of the input") {
        REQUIRE(front == inputs.begin());
      }
    }
    AND_WHEN("get back") {
      auto back = partition.get_back();
      THEN("it should be end of the input") { REQUIRE(back == inputs.end()); }
    }
  }

  GIVEN("more than one elements input partitioner") {
    std::array<int, 5> inputs{3, 5, 4, 8, 5};
    auto comp = [](const int &left, const int &right) { return left < right; };
    partitioner partition(inputs.begin(), inputs.end(), comp);
    WHEN("construct it") {
      THEN("it should put the last element in the ordered position") {
        REQUIRE(inputs[2] == 5);
      }
    }
    WHEN("get front") {
      auto front = partition.get_front();
      THEN("it should be begin of the input") {
        auto expected_front = inputs.begin() + 2;
        REQUIRE(front == expected_front);
      }
    }
    AND_WHEN("get back") {
      auto back = partition.get_back();
      THEN("it should be end of the input") {
        auto expected_back = inputs.begin() + 3;
        REQUIRE(back == expected_back);
      }
    }
  }
}

} // namespace sort_algo::quicksort

#endif // TEST
