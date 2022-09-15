#ifdef TEST
#include "addition.hpp"
#include <catch2/catch_test_macros.hpp>
#include "operation/equal/equal.hpp"

namespace algebra::arithmetic {

SCENARIO("addition test", "[addition]") {
  GIVEN("two matrix") {
    matrix left{{1, 1}, {2, 3}, {8, 4}}, right{{1, 4}, {3, 4}, {12, 5}};
    WHEN("they are in same format") {
      THEN("it should follow exchange rule") {
        REQUIRE(((left + right) == (right + left)));
      }
    }
  }
}

}  // namespace algebra::arithmetic
#endif  // TEST
