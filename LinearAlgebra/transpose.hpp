#pragma once

#include "transpose.h"

namespace algebra::arithmetic {

template <typename T>
inline matrix<T> transpose(const matrix<T> &m) {
  matrix<T> t(m.rows(), m.columns());
  for (size_t i = 0; i < t.columns(); ++i) {
    for (size_t j = 0; j < t.rows(); ++j) {
      pixel tid{i, j}, id{j, i};
      t[tid] = m[id];
    }
  }
  return t;
}
}  // namespace algebra::arithmetic