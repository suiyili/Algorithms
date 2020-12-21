#include "stdafx.hpp"
#include "identity_matrix.hpp"
#include "equal.hpp"

using namespace algebra;
using namespace algebra::matrices;

SCENARIO("identity matrix test", "[identity_matrix]") {
  GIVEN("dimensions as identity initialization") {
    const size_t dimentions = 5;
    identity_matrix identity(dimentions);

    WHEN("get rows") {
      THEN("it should return the initial dimensions") {
        REQUIRE(identity.rows() == dimentions);
      }
    }

    WHEN("get columns") {
      THEN("it should return the initial dimensions") {
        REQUIRE(identity.columns() == dimentions);
      }
    }

  }

  GIVEN("an identity matrix") {
    identity_matrix identity(3);

    WHEN("access by ordinal out of range") {
      THEN("it throw") {
        REQUIRE_THROWS_AS(identity(3, 0), out_of_range);
        REQUIRE_THROWS_AS(identity(2, 3), out_of_range);
      }
    }

    WHEN("read element") {
      THEN("it should return 0 if not main diagonal") {
        REQUIRE(identity(0, 1) == 0);
        REQUIRE(identity(1, 0) == 0);
      }
    }

    WHEN("read element") {
      THEN("it should return 1 on main diagonal") {
        REQUIRE(identity(0, 0) == 1);
        REQUIRE(identity(1, 1) == 1);
        REQUIRE(identity(2, 2) == 1);
      }
    }

    WHEN("get row or column") {
      THEN("it should return the row or column by the given ordinal") {
        algebra_vector expected{0, 0, 1};
        REQUIRE(are_equal(identity.row(2), expected));
        REQUIRE(are_equal(identity.column(2), expected));
      }
    }
  }
}