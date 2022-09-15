#ifdef TEST

#include "argument.hpp"
#include "generic/parameter_not_set_error/parameter_not_set_error.hpp"
#include <catch2/catch_test_macros.hpp>

namespace expression::evaluate {

SCENARIO("argument test", "[argument]") {

  GIVEN("an empty std::string") {
    WHEN("construct argument without text") {
      auto ctor = [] { argument arg(""); };
      THEN("throw exception") {
        REQUIRE_THROWS_AS(ctor(), std::invalid_argument);
      }
    }
  }

  GIVEN("an number std::string") {
    WHEN("get result") {
      argument arg("100");
      parameters params;
      auto a = arg.result_with(params);
      THEN("convert it to an argument") { REQUIRE(a == 100); }
    }
  }

  GIVEN("an param std::string but without corresponding parameter") {
    argument arg("s");
    parameters params;
    WHEN("get result") {
      THEN("throw exception") {
        REQUIRE_THROWS_AS(arg.result_with(params), parameter_not_set_error);
      }
    }
  }
  GIVEN("an param std::string with corresponding parameter") {
    argument arg("s");
    parameters params{{"s", 100}};

    AND_WHEN("get result") {
      auto a = arg.result_with(params);
      THEN("it should use the given value") { REQUIRE(a == 100); }
    }
  }
}
} // namespace expression::evaluate
#endif // TEST