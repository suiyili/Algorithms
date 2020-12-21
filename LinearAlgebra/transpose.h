#pragma once

#include "matrix.hpp"

using namespace algebra::matrices;

namespace algebra::arithmetic {

template <typename T>
matrix<T> transpose(const matrix<T> &m);

}  // namespace algebra::arithmetic