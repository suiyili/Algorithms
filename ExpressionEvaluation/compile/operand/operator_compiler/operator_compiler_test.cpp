#ifdef TEST

#include "operator_compiler.hpp"
#include "compile/compiler_mock/compiler_mock.hpp"
#include "compile/compile_utility/compile_utility.hpp"
#include <catch2/catch_test_macros.hpp>

namespace expression::compile {

SCENARIO("operator compiler test", "[operator_compiler]") {

  GIVEN("no operator") {
    operator_compiler compiler;

    WHEN("getting priority") {
      auto priority = compiler.get_priority();
      THEN("it should return level zero") {
        REQUIRE(priority == arithmetic_priority::level_zero);
      }
    }

    std::unique_ptr<compiler_i> null_compiler;
    AND_WHEN("it merges with an invalid(null) compiler") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(compiler.merge(move(null_compiler)),
                          std::invalid_argument);
      }
    }
  }

  GIVEN("arithmetic operators") {

    std::vector<std::pair<char, arithmetic_priority>> operator_mappings{
        {add_operator, arithmetic_priority::level_three},
        {subtract_operator, arithmetic_priority::level_three},
        {multiply_operator, arithmetic_priority::level_two},
        {divide_operator, arithmetic_priority::level_two},
        {exponentiate_operator, arithmetic_priority::level_one}};

    WHEN("getting priority") {
      for (auto [op, priority] : operator_mappings) {
        operator_compiler compiler(op);
        THEN("it should return corresponding levels") {
          REQUIRE(priority == compiler.get_priority());
        }
      }
    }
  }

  GIVEN("an operator compiler merged with first compiler") {

    auto first_to_merge = std::make_unique<compiler_mock>();
    auto first_handle = first_to_merge.get();
    operator_compiler compiler(add_operator);
    compiler.merge(move(first_to_merge));
    CHECK_FALSE(first_handle->merge_called());

    auto second_to_merge = std::make_unique<compiler_mock>();
    auto second_handle = second_to_merge.get();
    WHEN("it merges the second one") {
      THEN("both compilers merged won't get called") {
        REQUIRE_FALSE(first_handle->merge_called());
        REQUIRE_FALSE(second_handle->merge_called());
      }
    }
  }

  GIVEN("the compiler having merged once and two pending compilers to merge") {
    auto compiler_merged = std::make_unique<compiler_mock>();
    compiler_merged->set_priority(arithmetic_priority::level_zero);
    auto merged_handle = compiler_merged.get();
    operator_compiler compiler(add_operator);
    compiler.merge(move(compiler_merged));

    auto first_compiler_to_merge = std::make_unique<compiler_mock>(1U);
    auto first_handle = first_compiler_to_merge.get();
    auto second_compiler_to_merge = std::make_unique<compiler_mock>(2U);
    auto second_handle = second_compiler_to_merge.get();

    WHEN(
        "the first compiler to merge have less priority over second compiler") {
      first_compiler_to_merge->set_priority(arithmetic_priority::level_one);
      second_compiler_to_merge->set_priority(arithmetic_priority::level_three);
      compiler.merge(move(first_compiler_to_merge));
      compiler.merge(move(second_compiler_to_merge));
      THEN("second compiler merge is called") {
        REQUIRE_FALSE(merged_handle->merge_called());
        REQUIRE_FALSE(first_handle->merge_called());
        REQUIRE(second_handle->merge_called());
        REQUIRE(second_handle->get_mock_id_if_merged() == 1U);
      }
    }
    AND_WHEN(
        "the first compiler to merge have same priority as second compiler") {
      first_compiler_to_merge->set_priority(arithmetic_priority::level_two);
      second_compiler_to_merge->set_priority(arithmetic_priority::level_two);
      compiler.merge(move(first_compiler_to_merge));
      compiler.merge(move(second_compiler_to_merge));
      THEN("second compiler merge is called") {
        REQUIRE_FALSE(merged_handle->merge_called());
        REQUIRE_FALSE(first_handle->merge_called());
        REQUIRE(second_handle->merge_called());
        REQUIRE(second_handle->get_mock_id_if_merged() == 1U);
      }
    }
    AND_WHEN("the first compiler to merge have higher priority over second "
             "compiler") {
      first_compiler_to_merge->set_priority(arithmetic_priority::level_two);
      second_compiler_to_merge->set_priority(arithmetic_priority::level_one);
      compiler.merge(move(first_compiler_to_merge));
      compiler.merge(move(second_compiler_to_merge));
      THEN("second compiler merge is called") {
        REQUIRE_FALSE(merged_handle->merge_called());
        REQUIRE_FALSE(second_handle->merge_called());
        REQUIRE(first_handle->merge_called());
        REQUIRE(first_handle->get_mock_id_if_merged() == 2U);
      }
    }
  }
}
} // namespace expression::compile
#endif // TEST