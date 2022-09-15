#ifdef TEST

#include "division.hpp"
#include "evaluation/operand/mock/argument_compiler_mock/argument_compiler_mock.hpp"
#include <catch2/catch_test_macros.hpp>


using namespace std::string_view_literals;

namespace expression::evaluate {
std::unique_ptr<division> divide(const std::vector<std::string_view> &values);

SCENARIO("division test", "[division]") {

  GIVEN("two values with divisor zero") {

    const std::vector children_values{"1.3"sv, "0"sv};

    WHEN("get result") {

      auto operation = divide(children_values);
      THEN("it should overflow") {
        REQUIRE_THROWS_AS(operation->result_with({}), std::overflow_error);
      }
    }
  }

  GIVEN("two non-zero values") {
    const std::vector children_values{"1.3"sv, "2"sv};

    WHEN("get result") {
      auto operation = divide(children_values);
      auto actual_result = operation->result_with({});

      THEN("it should get first divided by the second") {
        REQUIRE(actual_result == (1.3 / 2));
      }
    }
  }

  GIVEN("two parameters") {

    const std::vector children_values{"a"sv, "b"sv};
    parameters params{{"a", 8.5}, {"b", 2}};

    WHEN("get result") {

      auto operation = divide(children_values);
      auto actual_result = operation->result_with(params);

      THEN("it should get first parameter divided by the second") {
        REQUIRE(actual_result == (8.5 / 2));
      }
    }
  }
}

std::unique_ptr<division> divide(const std::vector<std::string_view> &values) {
  std::vector<std::unique_ptr<compiler_i>> children;
  for (auto value : values) {
    children.emplace_back(std::make_unique<argument_compiler_mock>(value));
  }
  return std::make_unique<division>(children);
}
} // namespace expression::evaluate
#endif // TEST