#pragma once

#include "matrix.hpp"

using namespace algebra::matrices;

namespace algebra::arithmetic {
template <typename T>
bool is_markov(const matrix<T> &m);

}  // namespace algebra::arithmetic
