#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include "find_maximum_subarray.hpp"
#include <array>

namespace maximum_subarray {

SCENARIO("maximum subarray domain model test", "[maximum_subarray_finder]") {

  GIVEN("empty array") {
    std::array<int, 1> data{0};
    auto begin = data.begin();
    auto end = begin;
    WHEN("find its max sub array") {
      THEN("it should throw") {
        REQUIRE_THROWS_AS(find_maximum_subarray(begin, end), std::length_error);
      }
    }
  }

  GIVEN("one item array") {
    std::array<int, 1> data{3};
    WHEN("find its max sub array") {
      auto maximum = find_maximum_subarray(data.begin(), data.end());
      THEN("it should get the item") { REQUIRE(data[0] == maximum.sum()); }
    }
  }

  GIVEN("an array") {
    std::array<int, 16> data{
        {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7}};
    WHEN("find its max sub array") {
      auto max_sub = find_maximum_subarray(data.cbegin(), data.cend());

      THEN("it should return the max subarray and its value") {
        auto expected_begin = data.cbegin() + 7;
        auto expected_end = data.cbegin() + 11;

        std::array<int, 16>::value_type expected_max =
            accumulate(expected_begin, expected_end, 0);

        REQUIRE(max_sub.begin() == expected_begin);
        REQUIRE(max_sub.end() == expected_end);
        REQUIRE(max_sub.sum() == expected_max);
      }
    }
  }
}

} // namespace maximum_subarray

#endif // TEST