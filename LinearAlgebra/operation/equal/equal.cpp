#ifdef TEST
#include "equal.hpp"
#include <catch2/catch_test_macros.hpp>


namespace algebra::arithmetic {

SCENARIO("algebra vector equal test", "[equal]") {
  GIVEN("two vectors with different shape") {
    algebra_vector<int> vec1{1, 2, 4};
    algebra_vector<int> vec2{1, 2, 2, 3};
    WHEN("compare them") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(are_equal(vec1, vec2), std::invalid_argument);
      }
    }
  }

  GIVEN("two same vectors") {
    algebra_vector<int> vec1{1, 2, 3, 4};
    algebra_vector<int> vec2{1, 2, 3, 4};

    algebra_vector<double> vec3{1.0, 3.0, .0, .0};
    const auto tiny = epsilon<> / 10.;
    algebra_vector<double> vec4{1. + tiny, 3. - tiny, .0 + tiny, .0 - tiny};

    WHEN("compare them") {
      THEN("it return true for integral") { REQUIRE(are_equal(vec1, vec2)); }
      AND_THEN("it return true for floating") {
        REQUIRE(are_equal(vec3, vec4));
      }
    }
  }

  GIVEN("two different vectors with same shape") {
    algebra_vector<int> vec1{1, 5, 3, 4};
    algebra_vector<int> vec2{1, 2, 3, 4};

    algebra_vector<double> vec3{1.0, 3.0, .0, .0};
    const auto big = epsilon<> * 2;
    algebra_vector<double> vec4{1. + big, 3. - big, .0 + big, .0 - big};
    WHEN("compare them") {
      THEN("it return false for integral") {
        REQUIRE_FALSE(are_equal(vec1, vec2));
      }
      AND_THEN("it return false for floating") {
        REQUIRE_FALSE(are_equal(vec3, vec4));
      }
    }
  }
}

SCENARIO("matrix equal test", "[equal]") {
  GIVEN("two matrices with different shape") {
    matrix mx1{{1, 2, 4}, {1, 2, 3}};
    matrix mx2{{1, 2}, {2, 3}};
    WHEN("compare them") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(mx1 == mx2, std::invalid_argument);
      }
    }
  }

  GIVEN("two identical matrices") {
    matrix mx1{{1, 2, 4}, {1, 2, 3}};
    matrix mx2{{1, 2, 4}, {1, 2, 3}};

    matrix mx3{{1.0, 3.0}, {.0, .0}};
    const auto tiny = epsilon<> / 10.;
    matrix mx4{{1. + tiny, 3. - tiny}, {.0 + tiny, .0 - tiny}};

    WHEN("compare them") {
      THEN("it return true for integral") { REQUIRE((mx1 == mx2)); }
      AND_THEN("it return true for floating") { REQUIRE((mx3 == mx4)); }
    }
  }

  GIVEN("two different matrices with same shape") {
    matrix mx1{{1, 2, 4}, {1, 2, 3}};
    matrix mx2{{1, 2, 3}, {1, 2, 3}};
    matrix mx3{{1.0, 3.0}, {.0, .0}};
    const auto big = epsilon<> * 2;
    matrix mx4{{1. + big, 3. - big}, {.0 + big, .0 - big}};
    WHEN("compare them") {
      THEN("it return false for integral") { REQUIRE_FALSE((mx1 == mx2)); }
      AND_THEN("it return false for floating") { REQUIRE_FALSE((mx3 == mx4)); }
    }
  }
}

}  // namespace algebra::arithmetic
#endif  // TEST
