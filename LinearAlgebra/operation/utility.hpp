#pragma once

#include "../generic/algebra_types.hpp"
#include "../matrices/matrix/matrix.hpp"

using namespace algebra::matrices;
using namespace algebra::generic;

namespace algebra::arithmetic {

template <typename T>
void ensure_match(const algebra_vector<T> &left,
                  const algebra_vector<T> &right) {
  if (left.size() == right.size()) return;

  throw std::invalid_argument("given two vector are not comparable");
}

template <typename T>
void ensure_match(const matrix<T> &left, const algebra_vector<T> &right) {
  if (left.columns() == right.size()) return;

  throw std::invalid_argument("given vector and matrix are not comparable");
}

template <typename T>
void ensure_match(const matrix<T> &left, const matrix<T> &right) {
  if (left.rows() == right.rows() && left.columns() == right.columns()) return;
  throw std::invalid_argument("given two matrix are not comparable");
}

template <typename T>
bool ensure_square(const matrix<T> &m) {
  return m.rows() == m.columns();
}

}  // namespace algebra::matrices