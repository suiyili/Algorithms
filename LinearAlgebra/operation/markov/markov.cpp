#ifdef TEST
#include "markov.hpp"
#include <catch2/catch_test_macros.hpp>

namespace algebra::arithmetic {

	SCENARIO("markov test", "markov") {
  GIVEN("a matrix with any value not between 0 and 1") {
    matrix mmx({{0.7, 0.2, 0.1}, {0.1, 0.5, 0.4}, {1.1, -0.3, 0.2}});
    WHEN("check if it is markov matrix ") {
      THEN("it will return false") { REQUIRE_FALSE(is_markov(mmx)); }
    }
  }

  GIVEN("a matrix with row sum is not one") {
    matrix mmx({{0.8, 0.52}, {0.1, 0.9}});
    WHEN("check if it is markov matrix") {
      THEN("it will return false") { REQUIRE_FALSE(is_markov(mmx)); }
    }
  }

  GIVEN("a markov matrix") {
    matrix mmx({{0.7, 0.2, 0.1}, {0.1, 0.5, 0.4}, {.8, 0.1, 0.1}});
    WHEN("check if it is markov matrix ") {
      THEN("it will return true") { REQUIRE(is_markov(mmx)); }
    }
  }
}

}  // namespace algebra::arithmetic

#endif