#ifdef TEST

#include "parser_factory.hpp"
#include "parse/operator_parser/operator_parser.hpp"
#include "parse/function_parser/function_parser.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;
namespace expression::parse {

SCENARIO("test parser factory", "[parser_factory]") {
  std::string_view expr("sin(8,a+(b-30))"sv);

  GIVEN("an whole expression interval") {
    auto interval = std::make_pair(0U, expr.size());
    WHEN("check if it contains function") {
      THEN("it should be false") {
        REQUIRE_FALSE(has_function(expr, interval));
      }
    }
  }

  GIVEN("an operand interval after comma") {
    auto interval = std::make_pair(6U, 14U); // a+b-30
    WHEN("check if it contains function") {
      THEN("it should be false") {
        REQUIRE_FALSE(has_function(expr, interval));
      }
    }
  }

  GIVEN("an operand interval between parentheses") {
    auto interval = std::make_pair(8U, 14U); //(b-30)
    WHEN("check if it contains function") {
      THEN("it should be false") {
        REQUIRE_FALSE(has_function(expr, interval));
      }
    }
  }

  GIVEN("an function interval") {
    auto interval = std::make_pair(3, expr.size()); //(8,a+(b-30))
    WHEN("check if it contains function") {
      THEN("it should be true") { REQUIRE(has_function(expr, interval)); }
    }
  }
}

} // namespace expression::parse

#endif // TEST