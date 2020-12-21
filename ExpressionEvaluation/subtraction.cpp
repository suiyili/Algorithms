#include "subtraction.hpp"

namespace expression::evaluate {

subtraction::subtraction(const argument_compilers &compilers)
    : operand(compilers) {}

double subtraction::get_result(const std::valarray<double> &args) const {
  return args[0] - args[1];
}

}