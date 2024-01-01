#ifdef TEST
#include <catch2/catch_test_macros.hpp>
#include "partition.hpp"
#include <array>

namespace sort_algo {

SCENARIO("partition test", "[make_partition]") {

  GIVEN("empty input") {
    std::array<int, 0> inputs{};
    WHEN("make partition") {
      auto partition = make_partition(inputs);
      THEN("it should return begin/end") {
        REQUIRE(inputs.begin() == partition);
      }
    }
  }

  GIVEN("single element input") {
    std::array<int, 1> inputs{1};
    WHEN("make partition") {
      auto partition = make_partition(inputs);
      THEN("it should be begin of the input") {
        REQUIRE(partition == inputs.begin());
      }
    }
  }

  GIVEN("more than one elements input") {
    std::array<int, 5> inputs{3, 5, 4, 8, 5};
    WHEN("make partition") {
      auto partition = make_partition(inputs);
      THEN("it should split inputs with the last item") {
        for(auto i : std::ranges::subrange(inputs.begin(), partition))
          REQUIRE(i < *partition);
        for(auto i : std::ranges::subrange(partition, inputs.end()))
          REQUIRE(*partition <= i);
      }
    }
  }
}

} // namespace sort_algo::quicksort

#endif // TEST
