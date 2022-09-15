#ifdef TEST

#include "multiplication.hpp"
#include "evaluation/operand/mock/argument_compiler_mock/argument_compiler_mock.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;

namespace expression::evaluate {

std::unique_ptr<multiplication>
multiply(const std::vector<std::string_view> &values);

SCENARIO("multiplication test", "[multiplication]") {

  GIVEN("two values") {
    const std::vector children_values{"1.5"sv, "2"sv};

    WHEN("get result") {
      auto operation = multiply(children_values);
      auto actual_result = operation->result_with({});

      THEN("it should multiply the two values") {
        REQUIRE(actual_result == (1.5 * 2));
      }
    }
  }

  GIVEN("two parameters") {
    const std::vector children_values{"a"sv, "b"sv};
    parameters params{{"a", 8.5}, {"b", 4}};

    WHEN("get result with given values") {
      auto operation = multiply(children_values);
      auto actual_result = operation->result_with(params);

      THEN("it should multiply the two given params") {
        REQUIRE(actual_result == (8.5 * 4));
      }
    }
  }
}

std::unique_ptr<multiplication>
multiply(const std::vector<std::string_view> &values) {
  std::vector<std::unique_ptr<compiler_i>> children;
  for (auto value : values) {
    children.emplace_back(std::make_unique<argument_compiler_mock>(value));
  }
  return std::make_unique<multiplication>(children);
}

} // namespace expression::evaluate

#endif // TEST