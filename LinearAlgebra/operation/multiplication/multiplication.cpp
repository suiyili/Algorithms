#ifdef TEST
#include "multiplication.hpp"
#include <catch2/catch_test_macros.hpp>
#include "operation/equal/equal.hpp"
#include "operation/identity/identity.hpp"

namespace algebra::arithmetic {

SCENARIO("multiplication test", "[multiplication]") {
  GIVEN("given two matrices not match") {
    matrix left{{2, 1}, {-3, -1}};
    matrix right{{4, 3}, {-2, -2}, {-1, 1}};
    WHEN("multiply them") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(left * right, std::invalid_argument);
      }
    }
  }
  GIVEN("two different shape matrices") {
    matrix left{{2, 1}, {-3, -1}, {-2, 1}};
    matrix right{{4, 3, -1}, {-2, -2, 1}};
    WHEN("multiply them") {
      THEN("it will return the result") {
        decltype(left) expected{{6, 4, -1}, {-10, -7, 2}, {-10, -8, 3}};
        REQUIRE((expected == (left * right)));
      }
    }
  }
  GIVEN("two inversed matrices") {
    matrix left{{2, 1, -1}, {-3, -1, 2}, {-2, 1, 2}};
    matrix right{{4, 3, -1}, {-2, -2, 1}, {5, 4, -1}};
    WHEN("multiply them") {
      THEN("it will return identity matrix") {
        auto expected = make_identity<int>(3);
        REQUIRE((expected == (left * right)));
      }
    }
  }
}

}  // namespace algebra::arithmetic
#endif  // TEST
