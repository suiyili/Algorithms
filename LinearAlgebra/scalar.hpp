#pragma once

#include "scalar.h"

namespace algebra::arithmetic {

template<typename T>
inline matrix<T>& operator*=(matrix<T>& m, T scalar) {
  for (size_t i = 0U; i < m.columns(); ++i) {
    for (size_t j = 0U; j < m.rows(); ++j) {
      pixel id{i, j};
      m[id] *= scalar;
	}
  }
  return m;
}

template<typename T>
inline matrix<T> operator*(const matrix<T> &m, T scalar) {
  matrix<T> result(m);
  result *= scalar;
  return result;
}

template<typename T>
inline matrix<T> operator*(T scalar, const matrix<T>& m) {
  return m * scalar;
}
}