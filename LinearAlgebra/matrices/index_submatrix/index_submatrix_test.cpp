#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include "matrices/index_source_matrix/index_source_matrix.hpp"
#include "index_submatrix.hpp"

namespace algebra::matrices {

static bool operator==(const pixel &left, const pixel &right);

SCENARIO("index_submatrix test", "[index_submatrix]") {
  GIVEN("a 4*5 matrix as source") {
    index_source_matrix source(4, 5);
    WHEN("submatrix is built from it by skipping given row and column") {
      index_submatrix sub_mx(source, pixel{1, 3});
      THEN("its rows will be one less than the source matrix") {
        REQUIRE(sub_mx.rows() == (source.rows() - 1));
      }
      AND_THEN("its columns will be one less than the source matrix") {
        REQUIRE(sub_mx.columns() == source.columns() - 1);
      }

      AND_THEN("it should ignore the specified source row and column") {
        // keep the source
        auto sub_id = sub_mx[pixel{0, 1}];
        REQUIRE((sub_id == pixel{0, 1}));
        // just skip row
        sub_id = sub_mx[pixel{0, 3}];
        REQUIRE((sub_id == pixel{0, 4}));
        // just skip column
        sub_id = sub_mx[pixel{2, 1}];
        REQUIRE((sub_id == pixel{3, 1}));
        // skip both row and column
        sub_id = sub_mx[pixel{3, 3}];
        REQUIRE((sub_id == pixel{4, 4}));
      }
    }
  }
}

bool operator==(const pixel &left, const pixel &right) {
  return left.column == right.column && left.row == right.row;
}

}  // namespace algebra::matrices
#endif