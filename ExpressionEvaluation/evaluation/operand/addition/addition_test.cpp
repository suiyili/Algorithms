#ifdef TEST

#include "addition.hpp"
#include "evaluation/operand/mock/argument_compiler_mock/argument_compiler_mock.hpp"
#include <catch2/catch_test_macros.hpp>


using namespace std::string_view_literals;

namespace expression::evaluate {
std::unique_ptr<addition> add(const std::vector<std::string_view> &values);

SCENARIO("addtion test", "[addition]") {

  GIVEN("two values") {
    const std::vector children_values{"1.3"sv, "2"sv};
    WHEN("get result") {
      auto operation = add(children_values);
      auto actual_result = operation->result_with({});

      THEN("it passes a list of values to derived object") {
        REQUIRE(actual_result == (1.3 + 2));
      }
    }
  }

  GIVEN("two parameters") {

    const std::vector children_values{"a"sv, "b"sv};
    parameters params{{"a", 8.5}, {"b", 2}};

    WHEN("get result with given values") {
      auto operation = add(children_values);
      auto actual_result = operation->result_with(params);

      THEN("each child find value from the given params") {
        REQUIRE(actual_result == (8.5 + 2));
      }
    }
  }
}

std::unique_ptr<addition> add(const std::vector<std::string_view> &values) {
  std::vector<std::unique_ptr<compiler_i>> children;
  for (auto value : values) {
    children.emplace_back(std::make_unique<argument_compiler_mock>(value));
  }
  return std::make_unique<addition>(children);
}
} // namespace expression::evaluate
#endif // TEST