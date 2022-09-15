#pragma once

#include "multiplication.h"

namespace algebra::arithmetic {

template <typename T>
void ensure_match_multiply(const matrix<T>& left, const matrix<T>& right) {
  if (left.columns() == right.rows()) return;
  throw std::invalid_argument("not match for multiplication");
}

template <typename T>
inline matrix<T> multiply(const matrix<T>& left, const matrix<T>& right) {
  matrix<T> multiplication(right.columns(), left.rows());

  for (size_t i = 0; i < multiplication.columns(); ++i) {    
    for (size_t j = 0; j < multiplication.rows(); ++j) {
      auto row = left.row(j), column = right.column(i);
      pixel id{i, j};
      multiplication[id] = (row * column).sum();
    }
  }
  return multiplication;
}

template <typename T>
inline matrix<T> operator*(const matrix<T>& left, const matrix<T>& right) {
  ensure_match_multiply(left, right);
  return multiply(left, right);
}

}  // namespace algebra::matrices