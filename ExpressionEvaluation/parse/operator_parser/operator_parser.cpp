#include "operator_parser.hpp"
#include "parse/parse_utility.hpp"

using namespace std::string_view_literals;
using namespace expression::compile;


namespace expression::parse {
operator_parser::operator_parser(std::string_view expr, const view_interval& interval)
    : expr_(expr),
      interval_(interval),
      last_(children_.before_begin()) {}

view_interval operator_parser::get_interval() const {
  return interval_;
}

void operator_parser::append(parser_ptr child) {
  last_ = children_.insert_after(last_, move(child));
}

std::unique_ptr<compiler_i> operator_parser::create_compiler(compiler_factory_i &factory) {
  /*
   * extract intervals between children intervals.
   * create compilers from those intervals with symbol and operations
   * combined children parsers created compilers.
   * */

  auto top = factory.create_top();
  const auto slot_interval = get_slot_interval();

  if (is_negative(expr_[slot_interval.first]))
    top->merge(factory.create_argument(std::string_view("0"sv)));

  auto compile_interval = std::make_pair(slot_interval.first, slot_interval.first);
  for (auto &child : children_) {
    auto child_interval = child->get_interval();
    compile_interval.second = child_interval.first;
    add_children(*top, make_children(substr(expr_, compile_interval), factory));
    top->merge(child->create_compiler(factory));
    compile_interval.first = child_interval.second;
  }
  compile_interval.second = slot_interval.second;
  add_children(*top, make_children(substr(expr_, compile_interval), factory));
  return top;
}

bool operator_parser::is_negative(char ch) noexcept {
  return ch == subtract_operator;
}

view_interval operator_parser::get_slot_interval() const noexcept {
  if (!is_inside() && expr_[interval_.first] == to_char(interval_state::open))
    return std::make_pair(interval_.first + 1U, interval_.second - 1U);
  return interval_;
}

std::forward_list<std::unique_ptr<compiler_i>> operator_parser::make_children(std::string_view expr, compiler_factory_i &factory) {
  /*
   * get args between symbols,
   * create compilers from them
   * */
  constexpr std::string_view symbols(operators_.data(), operators_.size());
  std::forward_list<std::unique_ptr<compiler_i>> compilers;
  auto last = compilers.before_begin();

  view_interval interval = std::make_pair(0U, expr.find_first_of(symbols));

  while (interval.second != std::string_view::npos) {
    if (is_valid(interval))
      last = compilers.insert_after(last, factory.create_argument(substr(expr, interval)));
    last = compilers.insert_after(last, factory.create_operation(expr[interval.second]));
    interval.first = interval.second + 1U;
    interval.second = expr.find_first_of(symbols, interval.first);
  }
  interval.second = expr.size();
  if (is_valid(interval))
    compilers.insert_after(last, factory.create_argument(substr(expr, interval)));
  return compilers;
}

void operator_parser::add_children(compiler_i &top, std::forward_list<std::unique_ptr<compiler_i>> children) {
  while (!children.empty()) {
    top.merge(move(children.front()));
    children.pop_front();
  }
}

std::string_view operator_parser::substr(std::string_view expr, const view_interval& interval) noexcept {
  return expr.substr(interval.first, interval.second - interval.first);
}

bool operator_parser::is_valid(const view_interval &interval) noexcept {
  return interval.first < interval.second;
}

bool operator_parser::is_inside() const noexcept {
  if (!children_.empty()) {
    auto &front = children_.front();
    return front->get_interval().first == interval_.first;
  }
  return false;
}

}