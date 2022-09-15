#pragma once

#include "matrices/matrix/matrix.hpp"

using namespace algebra::matrices;

namespace algebra::arithmetic {

template <typename T>
bool are_equal(const algebra_vector<T> &left, const algebra_vector<T> &right);

template <typename T>
bool operator==(const matrix<T> &left, const matrix<T> &right);

}  // namespace algebra::arithmetic