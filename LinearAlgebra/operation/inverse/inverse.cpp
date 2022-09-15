#ifdef TEST
#include "inverse.hpp"
#include "generic/algebra_exception/algebra_exception.hpp"
#include <catch2/catch_test_macros.hpp>
#include "operation/equal/equal.hpp"

namespace algebra::arithmetic {

SCENARIO("inverse test", "[inverse]") {
  GIVEN("a singular matrix") {
    matrix source{{1.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {2.f, 0.f, 3.f}};
    WHEN("get inverse of an singular") {
      THEN("it will throw") { REQUIRE_THROWS_AS(~source, algebra_exception); }
    }
  }

  GIVEN("a 2*2 matrix") {
    matrix source{{4.f, 7.f}, {2.f, 6.f}};

    WHEN("get inverse of it") {
      auto inversed = ~source;
      THEN("it will get it") {
        matrix expected{{0.6f, -0.7f}, {-0.2f, 0.4f}};
        REQUIRE((inversed == expected));
      }
    }
  }
  GIVEN("a 3*3 matrix") {
    matrix source{{2.f, 1.f, -1.f}, {-3.f, -1.f, 2.f}, {-2.f, 1.f, 2.f}};
    WHEN("get inverse of it") {
      auto inversed = ~source;
      THEN("it will get it") {
        matrix expected{{4.f, 3.f, -1.f}, {-2.f, -2.f, 1.f}, {5.f, 4.f, -1.f}};
        REQUIRE((inversed == expected));
      }
    }
  }
}

}  // namespace algebra::arithmetic
#endif  // TEST
