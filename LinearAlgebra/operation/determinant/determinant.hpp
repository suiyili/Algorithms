#pragma once

#include "determinant.h"
#include "operation/utility.hpp"
#include "matrices/index_source_matrix/index_source_matrix.hpp"
#include "matrices/index_submatrix/index_submatrix.hpp"

namespace algebra::arithmetic {

template<typename T>
T determinant_of(index_matrix_i &index_matrix, const matrix<T> &source);

template <typename T>
inline T determinant_of(const matrix<T> &m) {
  ensure_square(m);
  index_source_matrix origin(m.columns(), m.rows());
  return determinant_of(origin, m);
}

template <typename T>
T determinant_of(index_matrix_i &im, const matrix<T> &source) {
  if (im.columns() == 1) {
    auto id = im[pixel{0, 0}];
    return source[id];
  }

  T total_determinant = zero<T>;

  for (size_t i = 0; i < im.columns(); ++i) {
    pixel cross{i, 0};
    index_submatrix sub_mx(im, cross);
    T sub_determinant = source[im[cross]] * determinant_of(sub_mx, source);

    if (i % 2 == 0)
      total_determinant += sub_determinant;
    else
      total_determinant -= sub_determinant;
  }
  return total_determinant;
}

}  // namespace algebra::arithmetic
