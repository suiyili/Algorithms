#ifdef TEST
#include "scalar.hpp"
#include <catch2/catch_test_macros.hpp>
#include "operation/equal/equal.hpp"

namespace algebra::arithmetic {

SCENARIO("scalar test", "[scalar]") {
  GIVEN("a matrix") {
    matrix mx{{1, 3}, {2, 6}};
    WHEN("multiply with scalar") {
      const typename decltype(mx)::value_type scalar = 4;
      THEN("it multiplies every element with the scalar") {
        decltype(mx) expected(mx);
        expected *= scalar;
        REQUIRE((mx * scalar == expected));
      }
    }
  }
}

}  // namespace algebra::arithmetic
#endif  // TEST
