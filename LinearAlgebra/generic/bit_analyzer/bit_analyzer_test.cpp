#ifdef TEST
#include <catch2/catch_test_macros.hpp>
#include "bit_analyzer.hpp"

namespace algebra::generic {

SCENARIO("bit analyzer test", "[bit_analyzer]") {
  GIVEN("a bit analyzer") {
    WHEN("move to next true") {
      bit_analyzer bits(0b10010011);
      unsigned char expected[4] = {0, 1, 3, 3};

      bits.move_start();
      THEN(
          "it will return the span between two true bits based on current "
          "position") {
        for (auto i : expected) {
          auto j = bits.move_next_true();
          REQUIRE(j != bits.no_next_true());
          REQUIRE(j == i);
        }
      }
    }

    WHEN("move to no next true") {
      bit_analyzer bits(0b00000001);
      bits.move_start();
      bits.move_next_true();
      THEN("it will return false") {
        REQUIRE(bits.move_next_true() == bits.no_next_true());
      }
    }
  }
}

}  // namespace algebra::generic
#endif