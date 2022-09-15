#ifdef TEST

#include "exponentiation.hpp"
#include "evaluation/operand/mock/argument_compiler_mock/argument_compiler_mock.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;

namespace expression::evaluate {

std::unique_ptr<exponentiation>
exponentiate(const std::vector<std::string_view> &values);

SCENARIO("exponentiation test", "[exponentiation]") {

  GIVEN("two values") {
    const std::vector children_values{"1.0"sv, "200"sv};

    WHEN("get result") {
      auto operation = exponentiate(children_values);
      auto actual_result = operation->result_with({});

      THEN("it should get power of first based on second") {
        REQUIRE(actual_result == pow(1.0, 200));
      }
    }
  }

  GIVEN("two parameters") {
    const std::vector children_values{"a"sv, "b"sv};
    parameters params{{"a", 3.5}, {"b", 2}};

    WHEN("get result with given paramters") {
      auto operation = exponentiate(children_values);
      auto actual_result = operation->result_with(params);

      THEN("it should get power of first based on second") {
        REQUIRE(actual_result == pow(3.5, 2));
      }
    }
  }
}

std::unique_ptr<exponentiation>
exponentiate(const std::vector<std::string_view> &values) {
  std::vector<std::unique_ptr<compiler_i>> children;
  for (auto value : values) {
    children.emplace_back(std::make_unique<argument_compiler_mock>(value));
  }
  return std::make_unique<exponentiation>(children);
}

} // namespace expression::evaluate
#endif // TEST