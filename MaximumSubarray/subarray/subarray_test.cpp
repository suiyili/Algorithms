#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include "subarray.hpp"
#include <stdexcept>
#include <valarray>

namespace generic {

SCENARIO("subarray test", "[subarray]") {

  GIVEN("boundary elements as input") {
    std::valarray values{4};
    auto ended = std::end(values);
    WHEN("construct subarray with no element") {
      subarray sub(ended, ended);
      THEN("the sum is zero") { REQUIRE(sub.sum() == 0); }
    }
  }

  GIVEN("an subarray") {
    const std::valarray values{2, -1, 3, 5, -2, 4};
    auto begin = std::begin(values) + 1;
    auto end = std::begin(values) + 5;

    subarray sub(begin, end);

    WHEN("get its two ends") {

      THEN("it can return the init ends") {
        REQUIRE(sub.begin() == begin);
        REQUIRE(sub.end() == end);
      }
    }

    WHEN("get sum of it") {
      auto max_value = sub.sum();
      THEN("it should return sum") {
        auto expected = values[std::slice(1, 4, 1)].sum();
        REQUIRE(max_value == expected);
      }
    }
  }
}

} // namespace maximum_subarray

#endif // TEST