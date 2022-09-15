#include "calculator.hpp"
#include "parse/expression_parser/expression_parser.hpp"

namespace expression {
void calculator::register_function(const std::string_view &name,
                                   evaluation_function user_function) {
  factory_.prepare(name, move(user_function));
}

std::unique_ptr<operand_i> calculator::compile(const std::string_view &exp) {
  parser_factory parser_factory_v;
  expression_parser general_parser(exp);
  auto parser_v = general_parser.create(parser_factory_v);
  auto compiler = parser_v->create_compiler(factory_);
  return compiler->compile();
}
} // namespace expression