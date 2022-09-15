#ifdef TEST

#include "board.hpp"
#include <catch2/catch_test_macros.hpp>
#include "board/cell_factory_mock/cell_factory_mock.hpp"

namespace game {

SCENARIO("board test", "[board]") {

  GIVEN("given a initial position") {

    cell_factory_mock cell_factory_v;
    std::vector<grid> init{grid(0, 0), grid(1, 1), grid(-1, 0)};
    board game_board(init);

    WHEN("getting next generation") {
      game_board.generate_next(cell_factory_v);

      THEN("it will call cell factory") {
        REQUIRE(cell_factory_v.create_called() > init.size());
      }

      AND_THEN("it will increase all cells neighbour number") {
        REQUIRE(cell_factory_v.all_cells_increase_called());
      }

      AND_THEN("it will check all cells alive") {
        REQUIRE(cell_factory_v.all_cells_alive_called());
      }
    }
  }
}

} // namespace game
#endif // TEST