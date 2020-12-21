#ifdef TEST

#include <catch2/catch.hpp>
#include "heap_sort.hpp"
#include <vector>

using namespace sortalgo;
using namespace sortalgo::heapsort;

SCENARIO("heap sort test", "[heap_sorter, heap_cursor]") {
  GIVEN("an ten elements array") {
    using ten_int_array = std::vector<int>;
    ten_int_array source{24, -15, -2, 8, -21, 33, -54, 66, 12, 0};
    ten_int_array expected_asc{-54, -21, -15, -2, 0, 8, 12, 24, 33, 66};
    ten_int_array expected_desc{66, 33, 24, 12, 8, 0, -2, -15, -21, -54};

    WHEN("do heap sort it by asc order") {

      auto comp = [](const int &left, const int &right) {
        return left < right;
      };

      heap_sort(source.begin(), source.end(), comp);
     
      THEN("it should be sorted by asc order in-place") {
        REQUIRE_THAT(source, Catch::Equals(expected_asc));
      }
    }

    AND_WHEN("sort it by desc order") {

      auto comp = [](const int &left, const int &right) {
        return left > right;
      };

      heap_sort(source.begin(), source.end(), comp);

      THEN("it should be sorted by desc order in-place") {
        REQUIRE_THAT(source, Catch::Equals(expected_desc));
      }
    }
  }
}
#endif // TEST