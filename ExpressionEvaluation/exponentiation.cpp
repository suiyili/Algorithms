#include "exponentiation.hpp"

namespace expression::evaluate {

exponentiation::exponentiation(const argument_compilers &compilers)
    : operand(compilers) {}

double exponentiation::get_result(const std::valarray<double> &args) const {
  return pow(args[0], args[1]);
}

}

