#pragma once

#include "evaluation/operand/operand.hpp"

namespace expression::evaluate {
class exponentiation final : public operand {
 public:
  explicit exponentiation(const argument_compilers &compilers);
  ~exponentiation() override = default;
 private:
  double get_result(const std::valarray<double> &args) const override;
};

}