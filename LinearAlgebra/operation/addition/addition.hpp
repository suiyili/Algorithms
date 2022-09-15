#pragma once

#include "addition.h"
#include "operation/utility.hpp"

namespace algebra::arithmetic {

template <typename T>
inline matrix<T> operator+(const matrix<T>& left, const matrix<T>& right) {
  ensure_match(left, right);
  matrix<T> sum(left.columns(), left.rows());

  for (size_t i = 0U; i < sum.columns(); ++i) {
    for (size_t j = 0U; j < sum.rows(); ++j) {
      pixel id{i, j};
      sum[id] = left[id] + right[id];
    }
  }
  return sum;
}

}  // namespace algebra::matrices