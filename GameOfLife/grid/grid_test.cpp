#ifdef TEST

#include "grid.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using namespace Catch::Matchers;

namespace game {

class neighbour_contains_matcher final : public MatcherBase<neighbours> {
public:
  neighbour_contains_matcher(const neighbours &comparator) noexcept;
  bool match(const neighbours &n) const override;
  std::string describe() const override;

private:
  const neighbours &comparator_;
};

static neighbour_contains_matcher Contains(const neighbours &n) noexcept;

SCENARIO("grids test", "[grid]") {
  GIVEN("given two grids with same coordinates") {
    const grid grid1(1, 3);
    const grid grid2(1, 3);

    WHEN("compare them") {
      THEN("they should be equal") { REQUIRE(grid1 == grid2); }
      AND_THEN("they have same hash value") {
        grid_hash hash_fn;
        const auto grid1_hash = hash_fn(grid1);
        const auto grid2_hash = hash_fn(grid2);

        REQUIRE(grid1_hash == grid2_hash);
      }
    }
  }

  GIVEN("given two grids with different coordinates") {
    const grid grid1(1, 3);
    const grid grid2(-1, 3);
    WHEN("compare them") {
      THEN("they should not be equal") { REQUIRE_FALSE(grid1 == grid2); }
    }
  }

  GIVEN("given a grid") {
    const grid grid_cell(1, 2);

    WHEN("getting neighbours") {
      const auto n = grid_cell.get_neighbours();
      THEN("it shoulds return all 8 neighbours of the given grid") {
        neighbours expected{{grid(2, 2), grid(0, 2), grid(1, 3), grid(1, 1),
                             grid(2, 3), grid(0, 1), grid(0, 3), grid(2, 1)}};

        REQUIRE_THAT(n, Contains(expected));
      }
    }
  }
}

neighbour_contains_matcher Contains(const neighbours &n) noexcept {
  return neighbour_contains_matcher(n);
}

neighbour_contains_matcher::neighbour_contains_matcher(
    const neighbours &comparator) noexcept
    : comparator_(comparator) {}

bool neighbour_contains_matcher::match(const neighbours &n) const {
  if (comparator_.size() > n.size())
    return false;

  for (auto &comp : comparator_)
    if (std::find(n.begin(), n.end(), comp) == n.end())
      return false;
  return true;
}

std::string neighbour_contains_matcher::describe() const {
  using namespace std::literals;
  return "Contains neighbour"s;
}

} // namespace game

#endif // TEST