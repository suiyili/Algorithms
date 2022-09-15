#pragma once

#include "evaluation/operand/operand.hpp"

namespace expression::evaluate {
class multiplication final : public operand {
 public:
  explicit multiplication(const argument_compilers &compilers);
  ~multiplication() override = default;

 private:
  double get_result(const std::valarray<double> &args) const override;
};

}
