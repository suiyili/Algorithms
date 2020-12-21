#pragma once

#include <valarray>

namespace algebra::generic {

template<typename T>
constexpr T zero = T(0);

template <typename T>
constexpr T one = T(1);

template<typename T = double>
constexpr T epsilon = T(0.000002);

template<typename T>
using algebra_vector = std::valarray<T>;

struct pixel { size_t column, row; };
}