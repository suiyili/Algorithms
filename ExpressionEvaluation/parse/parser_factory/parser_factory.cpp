#include "parser_factory.hpp"
#include "parse/operator_parser/operator_parser.hpp"
#include "parse/function_parser/function_parser.hpp"
#include "parse/parse_utility.hpp"
#include <cctype>

namespace expression::parse {
parser_ptr parser_factory::create_parser(std::string_view expr, view_interval interval) {
  if (has_function(expr, interval))
    return std::make_unique<function_parser>(expr, interval);
  else
    return std::make_unique<operator_parser>(expr, interval);
}

bool has_function(std::string_view expr, view_interval interval) {
  auto start = interval.first;
  return start > 0U && expr[start] == to_char(interval_state::open) &&
         std::isalnum(expr[start - 1]);
}

} // namespace expression::parse