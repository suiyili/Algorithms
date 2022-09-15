#pragma once

#include "generic/expression_types.hpp"
#include "evaluation/operand/operand.hpp"

namespace expression::evaluate {
class custom_function : public operand {
 public:
  custom_function(evaluation_function user_function, const argument_compilers &compilers);
  ~custom_function() override = default;
 private:
  double get_result(const std::valarray<double> &args) const override;
 private:
  evaluation_function user_function_;
};
}