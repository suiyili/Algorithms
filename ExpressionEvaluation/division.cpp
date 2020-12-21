#include "division.hpp"
#include <stdexcept>

namespace expression::evaluate {

division::division(const argument_compilers &compilers)
    : operand(compilers) {
}

double division::get_result(const std::valarray<double> &args) const {
  auto result = args[0] / args[1];
  if (std::isinf(result))
    throw std::overflow_error("divisor is zero");
  return result;
}

}

