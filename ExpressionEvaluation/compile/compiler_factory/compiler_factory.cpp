#include "compiler_factory.hpp"
#include "compile/compile_utility/compile_utility.hpp"
#include "compile/operand/argument_compiler/argument_compiler.hpp"
#include "compile/operand/operator_compiler/operator_compiler.hpp"
#include "compile/operand/function_compiler/function_compiler.hpp"
#include <stdexcept>

using namespace std::string_view_literals;
using namespace expression::compile;

namespace expression::compile {

compiler_factory::compiler_factory()
    : function_mapping_(
    {
        {"sin"sv, [](const std::valarray<double> &args) -> double { return sin(args[0]); }},
        {"cos"sv, [](const std::valarray<double> &args) -> double { return cos(args[0]); }},
        {"ln"sv, [](const std::valarray<double> &args) -> double { return log(args[0]); }},
        {"log"sv, [](const std::valarray<double> &args) -> double { return log(args[1]) / log(args[0]); }}
    }) {}

void compiler_factory::prepare(const std::string_view &function_name, const evaluation_function &user_function) {
  auto allowed_name = std::find_if(function_name.cbegin(), function_name.cend(), [](char c) { return !allow_in_name(c); });
  if (allowed_name != function_name.cend())
    throw std::runtime_error("not good function name");

  auto found_name = function_mapping_.find(function_name);
  if (found_name == function_mapping_.end())
    function_mapping_.emplace(make_pair(function_name, user_function));
}

std::unique_ptr<compiler_i> compiler_factory::create_top() {
  return std::make_unique<operator_compiler>();
}

std::unique_ptr<compiler_i> compiler_factory::create_argument(std::string_view arg) {
  return std::make_unique<argument_compiler>(arg);
}

std::unique_ptr<compiler_i> compiler_factory::create_operation(char arithmetic_operator) {
  return std::make_unique<operator_compiler>(arithmetic_operator);
}

std::unique_ptr<compiler_i> compiler_factory::create_function(std::string_view name) {
  auto found = function_mapping_.find(name);
  if (found == function_mapping_.end())
    throw std::invalid_argument("function not exists");
  return std::make_unique<function_compiler>(found->second);
}
}

