#ifdef TEST

#include "connect.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace Catch;

namespace tree::generic {
SCENARIO("connect test", "[connect]"){
  GIVEN("two nodes, from less than to"){
    std::size_t from = 3, to = 5;
    WHEN("construct the connect"){
      connect conn(from, to);
      THEN("the from and to will be switch"){
        REQUIRE(conn.from() == to);
        REQUIRE(conn.to() == from);
      }
    }  
  }
  
  GIVEN("two nodes, from greater than to") {
    std::size_t from = 4, to = 3;
    WHEN("construct the connect")
    {
      connect conn(from, to);
      THEN("the from and to will be switch")
      {
        REQUIRE(conn.from() == from);
        REQUIRE(conn.to() == to);
      }
    }
  }
}
}
#endif // TEST
