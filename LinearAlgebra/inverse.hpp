#pragma once

#include "identity.hpp"
#include "inverse.h"
#include "lu_decompose.hpp"
#include "utility.hpp"

namespace algebra::arithmetic {

template <typename T>
matrix<T> operator~(const matrix<T> &m) {
  ensure_square(m);

  auto dimensions = m.rows();

  auto identity = make_identity<T>(m.rows());

  lu_decompose decomp(m);
  matrix<T> inversed(dimensions);

  for (size_t i = 0; i < dimensions; ++i) {
    auto solved = decomp.solve(identity.row(i));
    for (size_t j = 0; j < solved.size(); ++j)
      inversed[pixel{i, j}] = solved[j];
  }

  return inversed;
}
}  // namespace algebra::arithmetic