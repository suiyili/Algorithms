#include "addition.hpp"

namespace expression::evaluate {

addition::addition(const argument_compilers &compilers)
    : operand(compilers) {}

double addition::get_result(const std::valarray<double> &args) const {
  return args[0] + args[1];
}

}

