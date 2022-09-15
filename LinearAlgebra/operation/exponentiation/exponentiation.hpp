#pragma once

#include "generic/bit_analyzer/bit_analyzer.hpp"
#include "exponentiation.h"
#include "operation/identity/identity.hpp"
#include "operation/multiplication/multiplication.hpp"
#include "operation/utility.hpp"
#include <stdexcept>

using namespace algebra::generic;

namespace algebra::arithmetic {

template <typename T>
inline matrix<T> operator^(const matrix<T> &base, size_t exponent) {
  ensure_square(base);
  if (exponent == 0) throw std::invalid_argument("exponent is 0");

  auto result = make_identity<T>(base.rows());

  auto current_base = base;
  bit_analyzer bit_expon(exponent);

  bit_expon.move_start();
  decltype(bit_expon.move_next_true()) span;
  while ((span = bit_expon.move_next_true()) != bit_expon.no_next_true()) {
    for (size_t i = 0; i < span; ++i) {
      current_base = multiply(current_base, current_base);
    }
    result = multiply(result, current_base);
  }

  return result;
}

}  // namespace algebra::arithmetic