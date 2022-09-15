#ifdef TEST

#include "bit_reverse_array.hpp"
#include "generic/complex_matcher/complex_matcher.hpp"
#include <catch2/catch_test_macros.hpp>

namespace fft::generic {

SCENARIO("test bit reverse array", "[bit_reverse_array]") {
  GIVEN("a eight bit length array") {
    complex_array<8> source = {real_complex{0.0, 7.0}, real_complex{1.0, 6.0},
                               real_complex{2.0, 5.0}, real_complex{3.0, 4.0},
                               real_complex{4.0, 3.0}, real_complex{5.0, 2.0},
                               real_complex{6.0, 1.0}, real_complex{7.0, 0.0}};
    WHEN("build bit reverse array") {
      bit_reverse_array reversed(source);
      THEN("it should reference the bit reverse index") {
        REQUIRE_THAT(reversed[0], equal_to(real_complex{0.0, 7.0}, 0.001));
        REQUIRE_THAT(reversed[1], equal_to(real_complex{4.0, 3.0}, 0.001));
        REQUIRE_THAT(reversed[2], equal_to(real_complex{2.0, 5.0}, 0.001));
        REQUIRE_THAT(reversed[3], equal_to(real_complex{6.0, 1.0}, 0.001));
        REQUIRE_THAT(reversed[4], equal_to(real_complex{1.0, 6.0}, 0.001));
        REQUIRE_THAT(reversed[5], equal_to(real_complex{5.0, 2.0}, 0.001));
        REQUIRE_THAT(reversed[6], equal_to(real_complex{3.0, 4.0}, 0.001));
        REQUIRE_THAT(reversed[7], equal_to(real_complex{7.0, 0.0}, 0.001));
      }
    }
  }
}
} // namespace fft::generic

#endif // TEST
