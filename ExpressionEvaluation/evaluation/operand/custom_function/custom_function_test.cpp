#ifdef TEST

#include "custom_function.hpp"
#include "evaluation/operand/mock/argument_compiler_mock/argument_compiler_mock.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;

namespace expression::evaluate {

std::unique_ptr<custom_function>
call(evaluation_function user_func,
     const std::vector<std::string_view> &values);

SCENARIO("custom function test", "[custom_function]") {

  auto fn = [](const std::valarray<double> &args) -> double {
    return args[0] + args[1];
  };

  GIVEN("two values") {
    const std::vector children_values{"1.3"sv, "2"sv};

    WHEN("call the function") {
      auto operation = call(fn, children_values);
      auto actual_result = operation->result_with({});

      THEN("it should get the function result") {
        REQUIRE(actual_result == fn({1.3, 2}));
      }
    }
  }

  GIVEN("two parameters") {
    const std::vector children_values{"a"sv, "b"sv};
    parameters params{{"a", 8.5}, {"b", 2.5}};

    WHEN("call the function") {

      auto operation = call(fn, children_values);
      auto actual_result = operation->result_with(params);

      THEN("it should use the parameters to get function result") {
        REQUIRE(actual_result == fn({8.5, 2.5}));
      }
    }
  }
}

std::unique_ptr<custom_function>
call(evaluation_function user_func,
     const std::vector<std::string_view> &values) {
  std::vector<std::unique_ptr<compiler_i>> children;
  for (auto value : values) {
    children.emplace_back(std::make_unique<argument_compiler_mock>(value));
  }
  return std::make_unique<custom_function>(move(user_func), children);
}

} // namespace expression::evaluate

#endif // TEST