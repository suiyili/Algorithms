#ifdef TEST

#include "application/calculator/calculator.hpp"
#include <catch2/catch_test_macros.hpp>

namespace expression {

SCENARIO("parentheses expression evaluation test",
         "[operand][operator_compiler]") {
  calculator calculator_v;

  GIVEN("just one parenthesis expression with mixed operations") {
    constexpr char exp[] = "45.4*2.2/(-1.4+6)/3-2^2";

    WHEN("evaluate it") {

      auto eval = calculator_v.compile(exp);
      parameters params;
      auto expected = eval->result_with(params);
      THEN("it should treat the parenthesis as an operand unit") {
        REQUIRE(expected == (45.4 * 2.2 / (-1.4 + 6) / 3 - pow(2, 2)));
      }
    }
  }

  GIVEN("an expression with multi parentheses in one level") {
    constexpr char exp[] = "(-45.4-2.2)*(1.4+0.6)^(-1+2)";

    WHEN("evaluate it") {

      auto eval = calculator_v.compile(exp);
      parameters params;
      auto expected = eval->result_with(params);
      THEN("it should treat each parenthesis as an operand unit") {
        REQUIRE(expected == ((-45.4 - 2.2) * pow((1.4 + 0.6), (-1 + 2))));
      }
    }
  }

  GIVEN("an expression with multi parentheses in multi level") {
    constexpr char exp[] = "((4.4^(2.2+1))-(1.4+6))*(-9+3)";

    WHEN("evaluate it") {

      auto eval = calculator_v.compile(exp);
      parameters params;
      auto expected = eval->result_with(params);
      THEN("it should treat each parenthesis as an operand unit based on "
           "level") {
        REQUIRE(expected == (((pow(4.4, (2.2 + 1))) - (1.4 + 6)) * (-9 + 3)));
      }
    }
  }

  GIVEN("an expression with parenthesis and parameters") {
    constexpr char exp[] = "((-a^(2.2+x))-(1.4+y))*(-9+3)";
    parameters params{{"a", 0.0}, {"x", 0.0}, {"y", 0.0}};
    auto eval = calculator_v.compile(exp);

    WHEN("evaluate it with 1st group params") {
      double a = 3, x = 2.4, y = 5.1;
      params["a"] = a;
      params["x"] = x;
      params["y"] = y;
      auto expected = eval->result_with(params);
      THEN("the evaluation is the calculation result") {
        REQUIRE(expected == (((-pow(a, (2.2 + x))) - (1.4 + y)) * (-9 + 3)));
      }
    }
    AND_WHEN("evaluate it with 2nd group params") {
      double a = 3.3, x = 2, y = 8.1;
      params["a"] = a;
      params["x"] = x;
      params["y"] = y;
      auto expected = eval->result_with(params);
      THEN("the evaluation is the calculation result") {
        REQUIRE(expected == (((-pow(a, (2.2 + x))) - (1.4 + y)) * (-9 + 3)));
      }
    }
  }
}

} // namespace expression
#endif // TEST