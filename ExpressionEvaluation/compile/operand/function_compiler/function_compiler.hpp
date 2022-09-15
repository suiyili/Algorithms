#pragma once

#include "generic/expression_types.hpp"
#include "generic/compiler_i.hpp"

namespace expression::compile {
class function_compiler final : public compiler_i {
 public:
  explicit function_compiler(evaluation_function user_function);
  ~function_compiler() override = default;

  arithmetic_priority get_priority() const override;
  void merge(std::unique_ptr<compiler_i> compiler) override;
  std::unique_ptr<operand_i> compile() const override;

 protected:
  argument_compilers arguments_;
  evaluation_function user_function_;
};
}