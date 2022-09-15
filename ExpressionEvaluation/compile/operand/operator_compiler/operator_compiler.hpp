#pragma once

#include "generic/compiler_i.hpp"

using namespace expression;
namespace expression::compile {

class operator_compiler final : public compiler_i {
 public:
  operator_compiler();
  explicit operator_compiler(char arithmetic_operator);
  ~operator_compiler() override = default;

  arithmetic_priority get_priority() const override;
  void merge(std::unique_ptr<compiler_i> compiler) override;
  std::unique_ptr<operand_i> compile() const override;

 private:
  constexpr static char top_ = '\0';
  static const std::unordered_map<char, arithmetic_priority> priority_table_;
  static arithmetic_priority get_priority(char arithmetic_operator);

  operator_compiler(char arithmetic_operator, unsigned char capacity);

  const char arithmetic_operator_;
  const arithmetic_priority priority_;

  argument_compilers children_;
};

}