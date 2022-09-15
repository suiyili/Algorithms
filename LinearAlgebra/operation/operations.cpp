#ifdef TEST
#include "operations.hpp"
#include <catch2/catch_test_macros.hpp>

namespace algebra::arithmetic {

SCENARIO("linear algebra matrix domain model test", "[operations]") {
  GIVEN("two matrices") {
    WHEN("doing mixed operations") {
      matrix mx1{{0, 1}, {2, -2}, {5, 8}}, mx2{{3, 2}, {-8, 6}, {-1, 1}};
      THEN("it throw if format is wrong") {
        REQUIRE_THROWS_AS(mx1 * (mx1 - mx2), std::invalid_argument);
      }
    }
  }

  GIVEN("four matrices") {
    WHEN("doing mixed operations") {
      matrix mx0{{0, 0}, {0, 0}, {0, 0}}, mx1{{0, 1}, {2, -2}},
          mx2{{3, 2}, {-8, 6}}, mx3{{2, 0, 1}, {3, 5, -2}},
          mx4{{1, 0}, {2, 5}, {2, 0}};

      auto result = mx3 * (mx0 - mx4) + ((mx1 ^ 2) - mx2);

      mx4 *= -1;
      auto step2 = multiply(mx3, mx4);
      auto step3 = multiply(mx1, mx1);
      step3 = step3 - mx2;
      auto expected = step2 + step3;

      THEN("it will return expected result") { REQUIRE((result == expected)); }
    }
  }

  GIVEN("a matrix") {
    WHEN("multiply it with its inverse") {
      matrix mx{{2.f, 4.f, 6.f}, {1.f, 1.f, 8.f}, {6.f, 4.f, 4.f}};
      auto id = make_identity<decltype(mx)::value_type>(3U);

      THEN("the result will be a identity") { REQUIRE(((mx * (~mx)) == id)); }
    }
  }
}
}  // namespace algebra::arithmetic

#endif  // TEST
