#pragma once

#include "markov.h"
#include "operation/utility.hpp"
#include <type_traits>

namespace algebra::arithmetic {
template <typename T>
bool is_markov(const matrix<T> &m) {
  static_assert(std::is_floating_point<T>::value,
                "type must be floating point");
  ensure_square(m);
  auto dim = m.rows();
  for (size_t i = 0; i < dim; ++i) {
    double row_sum = 0;
    for (size_t j = 0; j < dim; ++j) {
      auto value = m[pixel{j, i}];
      if (value < 0 || value > 1) return false;
      row_sum += value;
    }

    if (abs(row_sum - 1) > epsilon<T>) return false;
  }
  return true;
}

}  // namespace algebra::arithmetic
