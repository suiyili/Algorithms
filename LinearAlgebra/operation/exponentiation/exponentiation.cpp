#ifdef TEST
#include "exponentiation.hpp"
#include <catch2/catch_test_macros.hpp>
#include "operation/equal/equal.hpp"
#include "operation/identity/identity.hpp"

namespace algebra::arithmetic {

SCENARIO("matrix exponentiation test", "[exponentiation]") {
  GIVEN("a non square matrix") {
    matrix<int> m(2U, 3U);
    WHEN("do exponentiation on it") {
      THEN("it will throw") {
        auto call = [&m](size_t exponent) { auto a = m ^ exponent; };
        REQUIRE_THROWS_AS(call(2U), std::invalid_argument);
      }
    }
  }

  GIVEN("a identity matrix") {
    auto id = make_identity<int>(3U);
    WHEN("power ten times") {
      auto actual = id ^ 10U;
      THEN("the result should still be identity") { REQUIRE((actual == id)); }
    }
  }

  GIVEN("a matrix") {
    matrix m{{1, 1}, {1, 1}};
    WHEN("power eight times") {
      auto actual = m ^ 9U;
      matrix expect{{256, 256}, {256, 256}};
      THEN("the result should power eight times") {
        REQUIRE((actual == expect));
      }
    }
  }
}

}  // namespace algebra::arithmetic
#endif  // TEST
