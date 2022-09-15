#include "expression_parser.hpp"
#include "compile/compile_utility/compile_utility.hpp"
#include "generic/parse_error/parse_error.hpp"

using namespace expression::compile;

namespace expression::parse {
expression_parser::expression_parser(std::string_view expr)
    : top_(build_topological_expression(check_expression(expr))) {}

std::string_view expression_parser::check_expression(std::string_view expr) {
  if (expr.empty())
    throw std::invalid_argument("empty expression");
  return expr;
}

expression_parser::interval_node expression_parser::build_topological_expression(std::string_view expr) {
  /*
 * 1. transform and insert after:
 * 1.1 ( to ((
 * 1.2 , to )(
 * 1.3 ) to ))
 * 2. stack
 * 2.1 push back ( as new obj and pop back ) to close.
 * 2.2 merge to top if top is func, otherwise omit.
 * */
  std::string_view delimiters(delimiters_.data(), delimiters_.size());
  node_stack stack;
  stack.emplace_front(expr, 0U);
  auto delimiter = expr.find_first_of(delimiters, 0U);
  while (delimiter != std::string_view::npos) {
    switch (get_priority(expr, delimiter)) {
      case priority::open: {
        auto is_func = is_function(expr, delimiter);
        stack.emplace_front(expr, delimiter++);
        if (is_func)
          stack.emplace_front(expr, delimiter, true);
      }
        break;
      case priority::semi_close:close_last_child(stack, delimiter);
        stack.emplace_front(expr, ++delimiter, true);
        break;
      case priority::close:
        if (stack.front().is_inside())
          close_last_child(stack, delimiter);
        close_last_child(stack, ++delimiter);
        break;
    }
    delimiter = expr.find_first_of(delimiters, delimiter);
  }

  auto only = std::move(stack.front());
  only.close(expr.size());
  stack.pop_front();
  if (stack.empty())
    return only;

  throw parse_error("bad expression!");
}

expression_parser::priority expression_parser::get_priority(std::string_view expr, view_ordinal ordinal) noexcept {
  auto c = ordinal < expr.size() ? expr[ordinal] : to_char(interval_state::close);
  return priority_table_.at(priority_table_.count(c) ? c : to_char(interval_state::open));
}

void expression_parser::close_last_child(expression_parser::node_stack &stack, view_ordinal close_end) {
  auto top = std::move(stack.front());
  top.close(close_end);
  stack.pop_front();
  if (stack.empty())
    throw parse_error("bad expression");
  stack.front().append(std::move(top));
}

bool expression_parser::is_function(std::string_view expr,
                                    view_ordinal start) noexcept {
  return start > 0U && expr[start] == to_char(interval_state::open) &&
      allow_in_name(expr[start - 1]);
}

parser_ptr expression_parser::create(parser_factory_i &factory) {
  return top_.create(factory);
}

const std::unordered_map<char, expression_parser::priority> expression_parser::priority_table_ = {
    {to_char(interval_state::open), priority::open},
    {to_char(interval_state::semi_close), priority::semi_close},
    {to_char(interval_state::close), priority::close}
};

expression_parser::interval_node::interval_node(std::string_view expr,
                                                view_ordinal start,
                                                bool is_func_argv) noexcept
    : expr_(expr),
      interval_(std::make_pair(start, start)),
      is_inside_(is_func_argv) {}

expression_parser::interval_node::interval_node(expression_parser::interval_node &&other) noexcept
    : expr_(other.expr_),
      interval_(move(other.interval_)),
      children_(move(other.children_)),
      is_inside_(other.is_inside_) {}

void expression_parser::interval_node::append(interval_node child) {
  children_.push_back(std::move(child));
}

void expression_parser::interval_node::close(view_ordinal end_pos) noexcept {
  interval_.second = end_pos;
}

bool expression_parser::interval_node::is_inside() const noexcept {
  return is_inside_;
}

parser_ptr expression_parser::interval_node::create(parser_factory_i &factory) const {
  auto parser = factory.create_parser(expr_, interval_);
  for (auto &i : children_)
    parser->append(i.create(factory));
  return parser;
}

}
