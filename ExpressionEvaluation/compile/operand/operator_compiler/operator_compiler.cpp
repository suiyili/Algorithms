#include "operator_compiler.hpp"
#include "compile/compile_utility/compile_utility.hpp"
#include "evaluation/operand/addition/addition.hpp"
#include "evaluation/operand/subtraction/subtraction.hpp"
#include "evaluation/operand/multiplication/multiplication.hpp"
#include "evaluation/operand/division/division.hpp"
#include "evaluation/operand/exponentiation/exponentiation.hpp"
#include <stdexcept>

using namespace expression::evaluate;

namespace expression::compile {

operator_compiler::operator_compiler()
    : operator_compiler(top_, 1U) {}

operator_compiler::operator_compiler(char arithmetic_operator)
    : operator_compiler(arithmetic_operator, 2U) {}

operator_compiler::operator_compiler(char arithmetic_operator, unsigned char capacity)
    : arithmetic_operator_(arithmetic_operator),
      priority_(get_priority(arithmetic_operator)) {
  children_.reserve(capacity);
}

arithmetic_priority operator_compiler::get_priority(char arithmetic_operator) {
  auto found = priority_table_.find(arithmetic_operator);
  if (found == priority_table_.end())
    throw std::invalid_argument("it is not an operator");

  return found->second;
}

arithmetic_priority operator_compiler::get_priority() const {
  return priority_;
}

void operator_compiler::merge(std::unique_ptr<compiler_i> compiler) {
  if (!compiler)
    throw std::invalid_argument("building compiler should not be null");

  if (children_.size() == children_.capacity()) {

    decltype(auto) last = children_.back();

    //here use <= especially '='.
    //means a+b+c => (a+b)+c.
    if (last->get_priority() <= compiler->get_priority())
      last.swap(compiler);
    if (compiler)
      last->merge(move(compiler));
  } else
    children_.push_back(move(compiler));

}

std::unique_ptr<operand_i> operator_compiler::compile() const {
  switch (arithmetic_operator_) {
    case add_operator:return std::make_unique<addition>(children_);
    case subtract_operator:return std::make_unique<subtraction>(children_);
    case multiply_operator:return std::make_unique<multiplication>(children_);
    case divide_operator:return std::make_unique<division>(children_);
    case exponentiate_operator:return std::make_unique<exponentiation>(children_);
    default:return children_.front()->compile();
  }
}

const std::unordered_map<char, arithmetic_priority> operator_compiler::priority_table_ = {
    {add_operator, arithmetic_priority::level_three},
    {subtract_operator, arithmetic_priority::level_three},
    {multiply_operator, arithmetic_priority::level_two},
    {divide_operator, arithmetic_priority::level_two},
    {exponentiate_operator, arithmetic_priority::level_one},
    {top_, arithmetic_priority::level_zero}
};

}

