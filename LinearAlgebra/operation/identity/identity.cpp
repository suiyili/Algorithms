#ifdef TEST
#include "identity.hpp"
#include <catch2/catch_test_macros.hpp>


namespace algebra::arithmetic {

SCENARIO("identity matrix test", "[identity]") {
  GIVEN("a size") {
    size_t size = 2U;
    WHEN("make a matrix") {
      auto m = make_identity<int>(size);
      THEN("it should create identity matrix") {
        REQUIRE(m[pixel{0, 0}] == 1);
        REQUIRE(m[pixel{0, 1}] == 0);
        REQUIRE(m[pixel{1, 0}] == 0);
        REQUIRE(m[pixel{1, 1}] == 1);
      }
    }
  }
}

}  // namespace algebra::arithmetic

#endif  // TEST