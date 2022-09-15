#ifdef TEST

#include "application/calculator/calculator.hpp"
#include <catch2/catch_test_macros.hpp>

namespace expression {

SCENARIO("single arithmetic operator expression evaluation test",
         "[operand][operator_compiler]") {

  calculator calculator_v;

  GIVEN("a addition expression") {
    constexpr char exp[] = "32.2+4.5";

    WHEN("evaluate it") {
      auto eval = calculator_v.compile(exp);
      parameters params;
      auto expected = eval->result_with(params);
      THEN("the evaluation is the sum") { REQUIRE(expected == (32.2 + 4.5)); }
    }
  }

  GIVEN("a subtraction expression") {
    constexpr char exp[] = "32-4.5";

    WHEN("evaluate it") {
      auto eval = calculator_v.compile(exp);
      parameters params;
      auto expected = eval->result_with(params);
      THEN("the evaluation is the remaining") {
        REQUIRE(expected == (32 - 4.5));
      }
    }
  }

  GIVEN("a multiplication expression") {
    constexpr char exp[] = "-45*23";

    WHEN("evaluate it") {
      auto eval = calculator_v.compile(exp);
      parameters params;
      auto expected = eval->result_with(params);
      THEN("the evaluation is the production") {
        REQUIRE(expected == (-45 * 23));
      }
    }
  }

  GIVEN("a division expression") {
    constexpr char exp[] = "45/3";

    WHEN("evaluate it") {
      auto eval = calculator_v.compile(exp);
      parameters params;
      auto expected = eval->result_with(params);
      THEN("the evaluation is the divided") { REQUIRE(expected == (45.0 / 3)); }
    }
  }

  GIVEN("a division expression with 0 divisor") {
    constexpr char exp[] = "45/0";

    WHEN("evaluate it") {
      auto eval = calculator_v.compile(exp);
      THEN("throw overflow exception") {
        parameters params;
        REQUIRE_THROWS_AS(eval->result_with(params), std::overflow_error);
      }
    }
  }

  GIVEN("a exponentiation expression") {
    constexpr char exp[] = "-1.414^2";

    WHEN("evaluate it") {
      auto eva = calculator_v.compile(exp);
      THEN("it should be the power the first operand with the second") {
        parameters params;
        REQUIRE(eva->result_with(params) == (-pow(1.414, 2)));
      }
    }
  }
}

SCENARIO("multi operations arithmetic expression evaluation test",
         "[operand][operator_compiler]") {

  calculator calculator_v;

  GIVEN("multi addition expression") {
    constexpr char exp[] = "32+45+5.5+7";

    WHEN("evaluate it") {
      auto eval = calculator_v.compile(exp);
      parameters params;
      auto expected = eval->result_with(params);
      THEN("the evaluation is the sum") {
        REQUIRE(expected == (32 + 45 + 5.5 + 7));
      }
    }
  }

  GIVEN("multi subtraction expression") {
    constexpr char exp[] = "-45-32-5";

    WHEN("evaluate it") {
      auto eval = calculator_v.compile(exp);
      parameters params;
      auto expected = eval->result_with(params);
      THEN("the evaluation is the remaining") {
        REQUIRE(expected == (-45 - 32 - 5));
      }
    }
  }

  GIVEN("multiple multiplication expression") {
    constexpr char exp[] = "-45*2.3*1*3";

    WHEN("evaluate it") {
      auto eval = calculator_v.compile(exp);
      parameters params;
      auto expected = eval->result_with(params);
      THEN("the evaluation is the production") {
        REQUIRE(expected == (-45 * 2.3 * 1 * 3));
      }
    }
  }

  GIVEN("mixed different operations expression") {
    constexpr char exp[] = "45.4*2.2/1.4^3+6/3-2*3.3";

    WHEN("evaluate it") {
      auto eval = calculator_v.compile(exp);
      parameters params;
      auto expected = eval->result_with(params);
      THEN("the evaluation is the calculation result") {
        REQUIRE(expected == (45.4 * 2.2 / pow(1.4, 3) + 6.0 / 3 - 2 * 3.3));
      }
    }
  }

  GIVEN("mixed different operations expression with arguments") {
    constexpr char exp[] = "-a*2.2/1.4+x/3-y^x*3.3";
    auto eval = calculator_v.compile(exp);

    parameters params{{"a", 0.0}, {"x", 0.0}, {"y", 0.0}};

    WHEN("evaluate it with 1st group params") {
      double a = 3.0, x = 2.4, y = 5.1;
      params["a"] = a;
      params["x"] = x;
      params["y"] = y;
      auto expected = eval->result_with(params);
      THEN("the evaluation is the calculation based on the first group "
           "parameters") {
        REQUIRE(expected == (-a * 2.2 / 1.4 + x / 3 - pow(y, x) * 3.3));
      }
    }
    AND_WHEN("evaluate it with 2nd group params") {
      double a = 3.3, x = 2, y = 8.1;
      params["a"] = a;
      params["x"] = x;
      params["y"] = y;
      auto expected = eval->result_with(params);
      THEN("the evaluation is the calculation based on the second group "
           "parameters") {
        REQUIRE(expected == (-a * 2.2 / 1.4 + x / 3 - pow(y, x) * 3.3));
      }
    }
  }
}
} // namespace expression
#endif //TEST