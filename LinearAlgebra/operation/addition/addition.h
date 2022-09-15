#pragma once

#include "matrices/matrix/matrix.hpp"

using namespace algebra::matrices;

namespace algebra::arithmetic {

template <typename T>
matrix<T> operator+(const matrix<T>& left, const matrix<T>& right);

}  // namespace algebra::arithmetic