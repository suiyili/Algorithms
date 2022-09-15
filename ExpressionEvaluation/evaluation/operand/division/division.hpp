#pragma once

#include "evaluation/operand/operand.hpp"

namespace expression::evaluate {
class division final : public operand {
 public:
  explicit division(const argument_compilers &compilers);
  ~division() override = default;
 private:
  double get_result(const std::valarray<double> &args) const override;
};

}