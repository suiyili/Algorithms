#ifdef TEST

#include "cell/cell.hpp"
#include <catch2/catch_test_macros.hpp>
#include <tuple>

using namespace game;

SCENARIO("cell test", "[cell]") {

  GIVEN("given a cell") {
    WHEN("increase its neighbour more than 8 times") {
      cell c(true);
      constexpr auto size = std::tuple_size<neighbours>::value;
      for (neighbours::size_type i = 0; i < size; ++i)
        c.increase_neighbour();

      THEN("it will throw") {
        REQUIRE_THROWS_AS(c.increase_neighbour(), std::out_of_range);
      }
    }
  }

  GIVEN("given a living cell") {
    cell c(true);

    WHEN("there are no neighbour around it") {
      THEN("it will die") { REQUIRE_FALSE(c.alive()); }
    }

    AND_WHEN("there is one neighbour around it") {
      c.increase_neighbour();

      THEN("it will die") { REQUIRE_FALSE(c.alive()); }
    }

    WHEN("there are two neighbour around it") {
      for (unsigned char i = 0; i < 2; ++i)
        c.increase_neighbour();
      THEN("it will keep alive") { REQUIRE(c.alive()); }
    }

    WHEN("there are two neighbour around it") {
      for (unsigned char i = 0; i < 3; ++i)
        c.increase_neighbour();
      THEN("it will keep alive") { REQUIRE(c.alive()); }
    }

    WHEN("there are more than three neighbours around it") {
      for (unsigned char i = 0; i < 4; ++i)
        c.increase_neighbour();
      THEN("it will die") { REQUIRE_FALSE(c.alive()); }
    }
  }

  GIVEN("given a cell not exists") {
    cell c(false);

    WHEN("there are no neighbour around it") {
      THEN("it keeps no cell") { REQUIRE_FALSE(c.alive()); }
    }

    WHEN("there is one neighbour around it") {

      c.increase_neighbour();

      THEN("it keeps no cell") { REQUIRE_FALSE(c.alive()); }
    }

    WHEN("there are two neighbour around it") {

      for (unsigned char i = 0; i < 2; ++i)
        c.increase_neighbour();

      THEN("it keeps no cell") { REQUIRE_FALSE(c.alive()); }
    }

    WHEN("there are three neighbour around it") {

      for (unsigned char i = 0; i < 3; ++i)
        c.increase_neighbour();

      THEN("it will activate the cell") { REQUIRE(c.alive()); }
    }
  }
}

#endif // TEST
