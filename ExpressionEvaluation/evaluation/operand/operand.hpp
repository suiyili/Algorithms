#pragma once

#include "generic/operand_i.hpp"
#include "generic/compiler_i.hpp"
#include <valarray>

using namespace expression;

namespace expression::evaluate {
class operand : public operand_i {
 public:
  explicit operand(const argument_compilers &compilers);
  ~operand() override = default;

  double result_with(const parameters &params) const final;
 protected:
  using params_size = std::vector<double>::size_type;
 private:
  virtual double get_result(const std::valarray<double> &args) const = 0;

  static std::vector<std::unique_ptr<operand_i>> Init(const argument_compilers &compilers);

  const std::vector<std::unique_ptr<operand_i>> children_;
};

}