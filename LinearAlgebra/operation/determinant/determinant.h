#pragma once

#include "matrices/matrix/matrix.hpp"

using namespace algebra::matrices;

namespace algebra::arithmetic {

template <typename T>
T determinant_of(const matrix<T> &m);

}  // namespace algebra::arithmetic
