#pragma once

#include "matrices/matrix/matrix.hpp"

using namespace algebra::matrices;

namespace algebra::arithmetic {

template <typename T>
matrix<T>& operator*=(matrix<T>& m, T scalar);

template <typename T>
matrix<T> operator*(const matrix<T>& m, T scalar);

template <typename T>
matrix<T> operator*(T scalar, const matrix<T>& m);

}  // namespace algebra::arithmetic