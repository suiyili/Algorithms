#pragma once

#include "compiler_factory.hpp"
#include "parser_factory.hpp"

using namespace expression::compile;
using namespace expression::parse;

namespace expression {

class calculator {
public:
  void register_function(const std::string_view &name,
                         evaluation_function user_function);
  std::unique_ptr<operand_i> compile(const std::string_view &exp);

private:
  compiler_factory factory_;
};

} // namespace expression
