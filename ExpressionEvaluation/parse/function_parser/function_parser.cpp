#include "function_parser.hpp"
#include "compile/compile_utility/compile_utility.hpp"

using namespace expression::compile;

namespace expression::parse {
function_parser::function_parser(std::string_view expr, const view_interval& interval)
    : name_(read_name(expr, interval.first)),
      interval_(expand_interval(interval, name_)),
      last_(children_.before_begin()) {}

view_interval function_parser::get_interval() const {
  return interval_;
}

void function_parser::append(parser_ptr child) {
  last_ = children_.insert_after(last_, move(child));
}

std::unique_ptr<compiler_i> function_parser::create_compiler(compiler_factory_i &factory) {
  auto func = factory.create_function(name_);
  for (auto &child : children_)
    func->merge(child->create_compiler(factory));
  return func;
}

std::string_view function_parser::read_name(std::string_view expr, view_ordinal end) noexcept {

  for (view_ordinal i = 1U; i < end; ++i) {
    view_ordinal j = end - i;
    if (!allow_in_name(expr[j]))
      return expr.substr(++j, --i);
  }
  return expr.substr(0, end);
}

view_interval function_parser::expand_interval(view_interval original, std::string_view name) noexcept {
  return std::make_pair(original.first - name.size(), original.second);
}

}