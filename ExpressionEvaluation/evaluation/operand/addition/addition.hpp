#pragma once

#include "evaluation/operand/operand.hpp"

namespace expression::evaluate {
class addition final : public operand {
 public:
  explicit addition(const argument_compilers &compilers);
  ~addition() override = default;
 private:
  double get_result(const std::valarray<double> &args) const override;

};
}