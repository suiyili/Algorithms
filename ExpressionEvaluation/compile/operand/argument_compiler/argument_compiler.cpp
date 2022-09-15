#include "argument_compiler.hpp"
#include "evaluation/argument/argument.hpp"
#include <stdexcept>

using namespace expression::evaluate;

namespace expression::compile {
argument_compiler::argument_compiler(std::string_view arg) : arg_(arg) {}

arithmetic_priority argument_compiler::get_priority() const {
  return arithmetic_priority::level_zero;
}

void argument_compiler::merge(std::unique_ptr<compiler_i> compiler) {
  throw std::logic_error("argument can not merge other type of operand");
}

std::unique_ptr<operand_i> argument_compiler::compile() const {
  return std::make_unique<argument>(arg_);
}
}

