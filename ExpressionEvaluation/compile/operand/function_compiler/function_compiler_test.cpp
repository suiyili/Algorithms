#ifdef TEST

#include "function_compiler.hpp"
#include "compile/compiler_mock/compiler_mock.hpp"
#include <catch2/catch_test_macros.hpp>

namespace expression::compile {

SCENARIO("function compiler test", "[function_compiler]") {

  GIVEN("a function compiler") {
    function_compiler fn_c(
        [](const std::valarray<double> &) -> double { return 1; });

    WHEN("getting priority") {
      THEN("it should return level zero") {
        REQUIRE(fn_c.get_priority() == arithmetic_priority::level_zero);
      }
    }

    WHEN("merging an invalid(null) compiler, ") {
      auto compiler = std::unique_ptr<compiler_i>(nullptr);

      THEN("it should throw") {
        REQUIRE_THROWS_AS(fn_c.merge(move(compiler)), std::invalid_argument);
      }
    }

    WHEN("merging other compilers with different priorities") {
      auto first_compiler = std::make_unique<compiler_mock>();
      auto first_handle = first_compiler.get();
      auto second_compiler = std::make_unique<compiler_mock>();
      auto second_handle = second_compiler.get();
      first_compiler->set_priority(arithmetic_priority::level_three);
      second_compiler->set_priority(arithmetic_priority::level_one);

      THEN("it should not call those compilers merge") {
        fn_c.merge(move(first_compiler));
        fn_c.merge(move(second_compiler));
        REQUIRE_FALSE(first_handle->merge_called());
        REQUIRE_FALSE(second_handle->merge_called());
      }
    }
  }
}
} // namespace expression::compile
#endif // TEST