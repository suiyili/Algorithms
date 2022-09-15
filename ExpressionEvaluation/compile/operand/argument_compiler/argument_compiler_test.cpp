#ifdef TEST

#include "argument_compiler.hpp"
#include "compile/compiler_mock/compiler_mock.hpp"
#include <catch2/catch_test_macros.hpp>

namespace expression::compile {

SCENARIO("argument compiler test", "[argument_compiler]") {

  GIVEN("a numeric in std::string") {

    argument_compiler arg("5");

    WHEN("get priority") {
      THEN("it should return level zero priority") {
        REQUIRE(arg.get_priority() == arithmetic_priority::level_zero);
      }
    }

    WHEN("merge with other") {
      THEN("it should throw") {
        REQUIRE_THROWS_AS(arg.merge(std::make_unique<compiler_mock>()),
                          std::logic_error);
      }
    }
  }
}
} // namespace expression::compile
#endif // TEST