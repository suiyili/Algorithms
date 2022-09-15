#ifdef TEST

#include "argument_compiler_mock.hpp"
#include "evaluation/operand/mock/argument_mock/argument_mock.hpp"
#include <stdexcept>

argument_compiler_mock::argument_compiler_mock(std::string_view arg)
    : arg_(arg) {}

std::unique_ptr<operand_i> argument_compiler_mock::compile() const {
  return std::make_unique<argument_mock>(arg_);
}

arithmetic_priority argument_compiler_mock::get_priority() const {
  throw std::logic_error("not support");
}

void argument_compiler_mock::merge(std::unique_ptr<compiler_i>) {
  throw std::logic_error("not support");
}

#endif // TEST