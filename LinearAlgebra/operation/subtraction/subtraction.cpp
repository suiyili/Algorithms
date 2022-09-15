#ifdef TEST
#include "subtraction.hpp"
#include "matrices/matrix/matrix.hpp"
#include <catch2/catch_test_macros.hpp>
#include "operation/equal/equal.hpp"

namespace algebra::arithmetic {

SCENARIO("subtraction test", "[subtraction]") {
  GIVEN("given two matrices not match") {
    matrix left{{2, 1}, {-3, -1}};
    matrix right{{4, 3, -1}, {-2, -2, 1}};
    WHEN("multiply them") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(left - right, std::invalid_argument);
      }
    }
  }
  GIVEN("two same shape matrices") {
    matrix left{{1, 1}, {2, 3}, {8, 4}}, right{{1, 4}, {3, 4}, {12, 5}};
    WHEN("one takes away anoter") {
      THEN("it should return the subtraction") {
        matrix subtract{{0, -3}, {-1, -1}, {-4, -1}};
        REQUIRE((left - right == subtract));
      }
    }
  }
}

}  // namespace algebra::arithmetic
#endif  // TEST
