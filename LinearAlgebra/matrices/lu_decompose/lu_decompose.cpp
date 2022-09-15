#ifdef TEST
#include "lu_decompose.hpp"
#include "generic/algebra_exception/algebra_exception.hpp"
#include <catch2/catch_test_macros.hpp>
#include "operation/equal/equal.hpp"

namespace algebra::matrices {

using namespace algebra::arithmetic;

SCENARIO("LU decompose test", "[lu_decompose]") {
  GIVEN("init square matrix") {
    WHEN("it is intialized with singular square matrix") {
      matrix<float> mx{{1.f, 1.f, 1.f}, {2.f, 2.f, 5.f}, {4.f, 4.f, 8.f}};
      auto ctor = [&mx] { lu_decompose decomp(mx); };

      THEN("it will throw") { REQUIRE_THROWS_AS(ctor(), algebra_exception); }
    }

    /*maybe have row obj and tdd it to show detailed behavior
        WHEN("it is intialized") {
      square_matrix mx{{1, -2, 3},
                       {2, -5, 12},
                       {0, 2, -10}};
      lu_decompose decomp(mx);

      THEN("it should get LU") {

        square_matrix expected_lower{{1, 0, 0},
                                     {0, 1, 0},
                                     {0.5, 0.25, 1}};
        square_matrix expected_upper{{2, -5, 12},
                                     {0, 2, -10},
                                     {0, 0, -0.5}};
        REQUIRE(decomp.lower() == expected_lower);
        REQUIRE(decomp.upper() == expected_upper);
      }
    }*/
  }

  GIVEN("a vector") {
    WHEN("vector is not fit") {
      algebra_vector<float> b{8.f, -11.f, -3.f, 0.f};

      THEN("it will throw") {
        matrix<float> a{{2.f, 1.f, -1.f}, {-3.f, -1.f, 2.f}, {-2.f, 1.f, 2.f}};
        lu_decompose decomp(a);

        REQUIRE_THROWS_AS(decomp.solve(b), std::invalid_argument);
      }
    }

    WHEN("solving the equation") {
      matrix<float> a{{2.f, 1.f, -1.f}, {-3.f, -1.f, 2.f}, {-2.f, 1.f, 2.f}};
      algebra_vector<float> b{8.f, -11.f, -3.f};

      lu_decompose decomp(a);
      auto x = decomp.solve(b);

      THEN("it will solve variables") {
        algebra_vector<float> expected{2.f, 3.f, -1.f};

        REQUIRE(are_equal(x, expected));
      }
    }
  }
}

}  // namespace algebra::matrices
#endif  // TEST
