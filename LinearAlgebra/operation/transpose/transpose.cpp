#ifdef TEST
#include "transpose.hpp"
#include <catch2/catch_test_macros.hpp>
#include "operation/equal/equal.hpp"

namespace algebra::arithmetic {

SCENARIO("transpose matrix test", "[transpose]") {
  GIVEN("a matrix") {
    matrix m{{1, 2, 3}, {4, 5, 6}};
    WHEN("transpose it") {
      auto actual = transpose(m);
      THEN("the matrix will be transposed") {
        matrix expected{{1, 4}, {2, 5}, {3, 6}};
        REQUIRE((actual == expected));
      }
    }
  }
}

}  // namespace algebra::arithmetic
#endif  // TEST
