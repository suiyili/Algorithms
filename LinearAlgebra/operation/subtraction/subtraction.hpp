#pragma once

#include "subtraction.h"
#include "operation/utility.hpp"

namespace algebra::arithmetic {

template <typename T>
matrix<T> operator-(const matrix<T> &left, const matrix<T> &right) {
  ensure_match(left, right);
  matrix<T> subtract(left.columns(), left.rows());
  for (size_t i = 0U; i < subtract.columns(); ++i) {
    for (size_t j = 0U; j < subtract.rows(); ++j) {
      pixel id{i, j};
      subtract[id] = left[id] - right[id];
    }
  }
  return subtract;
}
}  // namespace algebra::arithmetic