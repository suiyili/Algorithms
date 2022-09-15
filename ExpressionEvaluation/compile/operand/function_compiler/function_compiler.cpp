#include "function_compiler.hpp"
#include "evaluation/operand/custom_function/custom_function.hpp"
#include <stdexcept>

using namespace expression::evaluate;

namespace expression::compile {
function_compiler::function_compiler(evaluation_function user_function)
    : user_function_(user_function) {}

arithmetic_priority function_compiler::get_priority() const {
  return arithmetic_priority::level_zero;
}

void function_compiler::merge(std::unique_ptr<compiler_i> compiler) {
  if (!compiler)
    throw std::invalid_argument("compiler is null");
  arguments_.push_back(move(compiler));
}

std::unique_ptr<operand_i> function_compiler::compile() const {
  return std::make_unique<custom_function>(user_function_, arguments_);
}

}