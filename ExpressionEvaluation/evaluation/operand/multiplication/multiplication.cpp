#include "multiplication.hpp"

namespace expression::evaluate {

multiplication::multiplication(const argument_compilers &compilers)
    : operand(compilers) {
}

double multiplication::get_result(const std::valarray<double> &args) const {
  return args[0] * args[1];
}

}

