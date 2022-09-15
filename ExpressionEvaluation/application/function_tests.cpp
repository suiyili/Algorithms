#ifdef TEST

#include "application/calculator/calculator.hpp"
#include "generic/parameter_not_set_error/parameter_not_set_error.hpp"
#include "generic/parse_error/parse_error.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;

namespace expression {

SCENARIO("function expression evaluation test",
         "[operand][function_compiler]") {

  calculator calculator_v;

  GIVEN("a expression with just built-in functions") {
    constexpr char exp[] = "cos(r)*3+sin(-4.2)-ln(2)";

    WHEN("evaluate it") {
      auto eval = calculator_v.compile(exp);
      double r = -10;
      parameters params{{"r", r}};
      auto expected = eval->result_with(params);
      THEN("the evaluation is the result") {
        REQUIRE(expected == (cos(r) * 3 + sin(-4.2) - log(2)));
      }
    }
  }

  GIVEN("an expression with non-function parentheses with comma in it") {
    constexpr char exp[] = "2*(r,100)+8";

    WHEN("evaluate it") {
      THEN("it should throw parse error") {
        REQUIRE_THROWS_AS(calculator_v.compile(exp), parse_error);
      }
    }
  }

  GIVEN("a expression with user defined functions") {
    constexpr char exp[] = "2*min(abs(r),100)+abs(-8)";

    calculator_v.register_function("min"sv,
                                   [](const std::valarray<double> &args) {
                                     return std::min(args[0], args[1]);
                                   });

    calculator_v.register_function(
        "abs"sv,
        [](const std::valarray<double> &args) { return abs(args[0]); });

    WHEN("evaluate it") {
      auto eval = calculator_v.compile(exp);
      double r = -90;
      parameters params{{"r", r}};
      auto expected = eval->result_with(params);
      THEN("the evaluation is the calculation") {
        REQUIRE(expected == (2 * std::min<double>(abs(r), 100) + abs(-8)));
      }
    }
  }

  GIVEN("a expression with user defined inner expressions") {
    constexpr char exp[] = "testfunc(a1,a2,a3)*5";

    calculator_v.register_function(
        "testfunc", [&calculator_v](const std::valarray<double> &args) {
          auto eva = calculator_v.compile("3*(5-3+x)^2*y-z");
          parameters params{{"x", args[0]}, {"y", args[1]}, {"z", args[2]}};
          return eva->result_with(params);
        });

    WHEN("evaluate it") {
      auto eval = calculator_v.compile(exp);
      double a1 = -8, a2 = 2, a3 = 10;
      parameters params{{"a1", a1}, {"a2", a2}, {"a3", a3}};
      auto expected = eval->result_with(params);
      THEN("the evaluation is the calculation") {
        REQUIRE(expected == ((3 * pow(5 - 3 + a1, 2) * a2 - a3) * 5));
      }
    }
  }
}

} // namespace expression

#endif // TEST
