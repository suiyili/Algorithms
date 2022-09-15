#pragma once

#include "evaluation/operand/operand.hpp"

namespace expression::evaluate {
class subtraction final : public operand {
 public:
  explicit subtraction(const argument_compilers &compilers);
  ~subtraction() override = default;

 private:
  double get_result(const std::valarray<double> &args) const override;
};

}