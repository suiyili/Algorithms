#ifdef TEST
#include "determinant.hpp"
#include <array>
#include <catch2/catch_test_macros.hpp>

namespace algebra::arithmetic {

SCENARIO("determinant of matrix test", "[determinant]") {
  GIVEN("a 2*2 matrix") {
    matrix mx{{1, 2}, {3, 8}};
    WHEN("get determinant of it") {
      auto determinant = determinant_of(mx);
      THEN("it should get its determinant") {
        std::array<pixel, 4U> ids{pixel{0, 0}, pixel{1, 1}, pixel{1, 0},
                                  pixel{0, 1}};
        auto expected = mx[ids[0]] * mx[ids[1]] - mx[ids[2]] * mx[ids[3]];
        REQUIRE(determinant == expected);
      }
    }
  }

  GIVEN("a 3*3 matrix") {
    matrix mx{{1, 2, 4}, {3, 2, 1}, {3, 1, 4}};

    WHEN("get determinant of it") {
      auto determinant = determinant_of(mx);
      THEN("it should create identity matrix") {
        std::array<pixel, 18U> ids{
            pixel{0, 0}, pixel{1, 1}, pixel{2, 2}, pixel{1, 0}, pixel{2, 1},
            pixel{0, 2}, pixel{2, 0}, pixel{0, 1}, pixel{1, 2}, pixel{2, 0},
            pixel{1, 1}, pixel{0, 2}, pixel{1, 0}, pixel{0, 1}, pixel{2, 2},
            pixel{0, 0}, pixel{2, 1}, pixel{1, 2}};
        auto expected = mx[ids[0]] * mx[ids[1]] * mx[ids[2]] +
                        mx[ids[3]] * mx[ids[4]] * mx[ids[5]] +
                        mx[ids[6]] * mx[ids[7]] * mx[ids[8]] -
                        mx[ids[9]] * mx[ids[10]] * mx[ids[11]] -
                        mx[ids[12]] * mx[ids[13]] * mx[ids[14]] -
                        mx[ids[15]] * mx[ids[16]] * mx[ids[17]];

        REQUIRE(determinant == expected);
      }
    }
  }
}

}  // namespace algebra::arithmetic

#endif  // TEST
