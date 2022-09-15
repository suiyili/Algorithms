
#include "board/board.hpp"
#include "cell_factory/cell_factory.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <string>


using namespace Catch::Matchers;

namespace game {

using grids = std::vector<grid>;
using grid_iterator = grids::const_iterator;


class grid_matcher final : public MatcherBase<grids> {
public:
  grid_matcher(const grid &expected);
  virtual bool match(const grids &v) const override;
  virtual std::string describe() const override;

private:
  const grid &expected_;
};

// The builder function
static grid_matcher VectorNotContains(const grid &g);

SCENARIO("game of life acceptance tests", "[board][grid][cell]") {

  cell_factory cell_factory_v;

  GIVEN("given a cell without neighbours") {

    board b({grid(0, 0)});

    WHEN("board produces next generation") {

      b.generate_next(cell_factory_v);

      THEN("the cell will die") {
        const auto &positions = b.get_cells();
        REQUIRE(positions.empty());
      }
    }
  }

  GIVEN("given a cell with only one neighbour") {
    grid target_cell(0, 0);
    grid neighbour_cell(1, 1);
    board b({target_cell, neighbour_cell});

    WHEN("board produces next generation") {

      b.generate_next(cell_factory_v);

      THEN("it will die") {
        const auto &positions = b.get_cells();
        REQUIRE_THAT(positions, VectorNotContains(target_cell));
      }
    }
  }

  GIVEN("given a cell with two neighbours") {
    grid target_cell(0, 0);
    grids init_cells{target_cell, grid(1, 1), grid(-1, -1)};

    board b(init_cells);

    WHEN("board produces next generation") {

      b.generate_next(cell_factory_v);

      THEN("it will keep alive") {
        const auto &positions = b.get_cells();
        REQUIRE_THAT(positions, VectorContains(target_cell));
      }
    }
  }

  GIVEN("given a cell with three neighbours") {
    grid target_cell(0, 0);
    grids init_cells{target_cell, grid(1, 1), grid(-1, 0), grid(-1, -1)};

    board b(init_cells);
    WHEN("board produces next generation") {

      b.generate_next(cell_factory_v);
      THEN("it will keep alive") {
        const auto &positions = b.get_cells();
        REQUIRE_THAT(positions, VectorContains(target_cell));
      }
    }
  }

  GIVEN("given a cell with more than three neighbours") {

    grid target_cell(0, 0);
    grids init_cells{target_cell, grid(1, 1), grid(-1, 0), grid(0, 1),
                     grid(-1, -1)};

    board b(init_cells);
    WHEN("board produces next generation") {

      b.generate_next(cell_factory_v);

      THEN("it will die") {
        const auto &positions = b.get_cells();
        REQUIRE_THAT(positions, VectorNotContains(target_cell));
      }
    }
  }
  GIVEN("given a position surrounded with more than three neighbours") {

    grid target_position(0, 0);
    grids init_cells{grid(1, 1), grid(-1, 0), grid(0, 1), grid(-1, -1)};
    board b(init_cells);

    WHEN("board produces next generation") {
      b.generate_next(cell_factory_v);

      THEN("it still doesn't have cell") {
        const auto &positions = b.get_cells();

        REQUIRE_THAT(positions, VectorNotContains(target_position));
      }
    }
  }

  GIVEN("given a position with just three neighbours") {
    grid target_position(0, 0);
    grids init_cells{grid(1, 1), grid(-1, 0), grid(0, 1)};
    board b(init_cells);

    WHEN("board produces next generation") {
      b.generate_next(cell_factory_v);

      THEN("it will be a cell in next generation") {
        const auto &positions = b.get_cells();
        REQUIRE_THAT(positions, VectorContains(target_position));
      }
    }
  }

  GIVEN("given four living cells togehter like block") {
    grids init_cells{grid(0, 0), grid(1, 0), grid(0, 1), grid(1, 1)};
    board b(init_cells);
    WHEN("board produces next generation") {

      b.generate_next(cell_factory_v);

      THEN("they keep alive in places") {
        const auto &gen = b.get_cells();
        REQUIRE_THAT(gen, UnorderedEquals(init_cells));
      }
    }
  }

  GIVEN("given six living cells like beehive") {
    grids init_cells{grid(0, 0), grid(1, 1),  grid(1, -1),
                     grid(2, 1), grid(2, -1), grid(3, 0)};
    board b(init_cells);

    WHEN("board produces next generation") {
      b.generate_next(cell_factory_v);

      THEN("they keep alive in places") {
        const auto &gen = b.get_cells();
        REQUIRE_THAT(gen, UnorderedEquals(init_cells));
      }
    }
  }

  GIVEN("given living cells together like oscillators") {

    cell_factory cell_factory_v;

    WHEN("board produces next generation") {
      grids horizon_cells{grid(-1, 0), grid(0, 0), grid(1, 0)};
      grids verticle_cells{grid(0, 1), grid(0, 0), grid(0, -1)};

      board b(horizon_cells);

      THEN("they change between horizontal and vetial") {
        b.generate_next(cell_factory_v);
        const auto &gen = b.get_cells();
        REQUIRE_THAT(gen, UnorderedEquals(verticle_cells));
      }
    }
  }
}

inline grid_matcher VectorNotContains(const grid &g) { return {g}; }

grid_matcher::grid_matcher(const grid &expected) : expected_(expected) {}

bool grid_matcher::match(const grids &v) const {
  return std::find(v.begin(), v.end(), expected_) == v.end();
}

std::string grid_matcher::describe() const {
  using namespace std::literals::string_literals;
  return "Not contains given grid"s;
}

} // namespace game