#pragma once

#include "matrices/matrix/matrix.hpp"

using namespace algebra::matrices;

namespace algebra::arithmetic {

template <typename T>
matrix<T> make_identity(size_t size);

}  // namespace algebra::arithmetic
