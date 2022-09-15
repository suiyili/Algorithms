#ifdef TEST

#include "subtraction.hpp"
#include "evaluation/operand/mock/argument_compiler_mock/argument_compiler_mock.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;

namespace expression::evaluate {

std::unique_ptr<subtraction>
subtract(const std::vector<std::string_view> &values);

SCENARIO("subtraction test", "[subtraction]") {

  GIVEN("two values") {
    const std::vector children_values{"10.3"sv, "2"sv};

    WHEN("get result") {
      auto operation = subtract(children_values);
      auto actual_result = operation->result_with({});

      THEN("it should get the first subtract the second") {
        REQUIRE(actual_result == (10.3 - 2));
      }
    }
  }

  GIVEN("two parameters") {
    const std::vector children_values{"a"sv, "b"sv};
    parameters params{{"a", 20.5}, {"b", 2}};

    WHEN("get result with params") {

      auto operation = subtract(children_values);
      auto actual_result = operation->result_with(params);

      THEN("it should get the first parameter subtract the second") {
        REQUIRE(actual_result == (20.5 - 2));
      }
    }
  }
}

std::unique_ptr<subtraction>
subtract(const std::vector<std::string_view> &values) {
  std::vector<std::unique_ptr<compiler_i>> children;
  for (auto value : values) {
    children.emplace_back(std::make_unique<argument_compiler_mock>(value));
  }
  return std::make_unique<subtraction>(children);
}

} // namespace expression::evaluate

#endif // TEST