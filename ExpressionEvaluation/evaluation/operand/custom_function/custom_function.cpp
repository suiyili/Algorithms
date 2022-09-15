#include "custom_function.hpp"

namespace expression::evaluate {
custom_function::custom_function(evaluation_function user_function, const argument_compilers &compilers)
    : operand(compilers),
      user_function_(move(user_function)) {}

double custom_function::get_result(const std::valarray<double> &args) const {
  return user_function_(args);
}
}