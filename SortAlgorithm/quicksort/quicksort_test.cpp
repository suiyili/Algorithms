#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include "quicksort.hpp"
#include <array>

using namespace Catch::Matchers;

namespace sort_algo {

SCENARIO("quick sort algo test", "[quick_sorter]") {
  GIVEN("an ten elements array") {
    using ten_int_array = std::vector<int>;
    ten_int_array source{24, -15, -2, 8, -21, 33, -54, 66, 24, 0};
    ten_int_array expected_asc{-54, -21, -15, -2, 0, 8, 24, 24, 33, 66};
    ten_int_array expected_desc{66, 33, 24, 24, 8, 0, -2, -15, -21, -54};

    WHEN("sort it by asc order") {
      auto comp = [](const int &left, const int &right) {
        return left < right;
      };
      quicksort(source.begin(), source.end(), comp);
      THEN("it should be sorted by asc order in-place") {
        REQUIRE_THAT(source, Equals(expected_asc));
      }
    }

    AND_WHEN("sort it by desc order") {
      auto comp = [](const int &left, const int &right) {
        return left > right;
      };
      quicksort(source.begin(), source.end(), comp);
      THEN("it should be sorted by desc order in-place") {
        REQUIRE_THAT(source, Equals(expected_desc));
      }
    }
  }
}

} // namespace sort_algo::quicksort

#endif // TEST