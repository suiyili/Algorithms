#ifdef TEST

#include <catch2/catch_test_macros.hpp>

#include "fourier_transform/inverse_transform/inverse_transform.hpp"
#include "fourier_transform/polynomial_transform/polynomial_transform.hpp"
#include "generic/complex_matcher/complex_matcher.hpp"

using namespace fft::generic;

namespace fft::transform {

SCENARIO("test fast fourier transform", "[fourier_transform]") {
  GIVEN("an paramters array") {
    complex_array<8> input = {real_complex{1.0, 0.0}, real_complex{2.0, 0.0},
                              real_complex{1.5, 0.0}, real_complex{2.5, 0.0},
                              real_complex{3.0, 0.0}, real_complex{4.0, 0.0},
                              real_complex{5.5, 0.0}, real_complex{7.0, 0.0}};
    polynomial_transform forward_trans;
    auto intermediam = forward_trans.transform(input);
    inverse_transform inverse_trans;
    auto output = inverse_trans.transform(intermediam);
    REQUIRE_THAT(input[0], equal_to(output[0], 0.001));
    REQUIRE_THAT(input[1], equal_to(output[1], 0.001));
    REQUIRE_THAT(input[2], equal_to(output[2], 0.001));
    REQUIRE_THAT(input[3], equal_to(output[3], 0.001));
    REQUIRE_THAT(input[4], equal_to(output[4], 0.001));
    REQUIRE_THAT(input[5], equal_to(output[5], 0.001));
    REQUIRE_THAT(input[6], equal_to(output[6], 0.001));
    REQUIRE_THAT(input[7], equal_to(output[7], 0.001));
  }
}

}  // namespace fft::transform

#endif  // TEST
