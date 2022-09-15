#pragma once

#include "lu_decompose.h"
#include "generic/algebra_exception/algebra_exception.hpp"
#include "generic/algebra_types.hpp"
#include <type_traits>
#include <utility>
#include <cmath>

using namespace algebra::generic;

namespace algebra::matrices {

template <typename T>
inline lu_decompose<T>::lu_decompose(const matrix<T> &equation)
    : dimensions_(equation.rows()),
      data_(dimensions_ * dimensions_),
      pivot_(dimensions_) {
  init_source(equation);
  diagonalize();
}

template <typename T>
inline algebra_vector<T> lu_decompose<T>::solve(const algebra_vector<T> &equal_to) {
  if (equal_to.size() != dimensions_) throw std::invalid_argument("size is not fit");
  auto pivoted = apply_pivot(equal_to);
  auto d = forward_substitute(pivoted);
  return back_substitute(d);
}

template <typename T>
inline T &lu_decompose<T>::get_value(const pixel &id) {
  return data_[id.row * dimensions_ + id.column];
}

template <typename T>
inline void lu_decompose<T>::init_source(const matrix<T> &source) {
  for (size_t i = 0; i < dimensions_; ++i) {
    pivot_[i] = i;
    for (size_t j = 0; j < dimensions_; ++j) {
      pixel id{j, i};
      get_value(id) = source[id];
    }
  }
}

template <typename T>
inline void lu_decompose<T>::diagonalize() {
  for (size_t i = 0; i < (dimensions_ - 1); ++i) {
    swap_max_below(i);
    diagonalize(i);
  }
}

template <typename T>
inline void lu_decompose<T>::swap_max_below(size_t row) {
  auto max_row = row;
  auto max_value = get_value(pixel{row, row});

  for (size_t i = row + 1; i < dimensions_; ++i) {
    auto v = abs(get_value(pixel{row, i}));
    if ( v > max_value) {
      max_row = i;
      max_value = v;
    }
  }

  if constexpr (std::is_integral_v<T>) {
    if (max_value == 0)
      throw algebra_exception("the given matrix has no solution");
  } else {
    if (max_value < epsilon<T>)
      throw algebra_exception("the given matrix has no solution");
  }
    

  

  swap_row(row, max_row);
}

template <typename T>
inline void lu_decompose<T>::swap_row(size_t row1, size_t row2) {
  if (row1 == row2) return;

  for (size_t j = 0; j < dimensions_; ++j)
    std::swap(get_value(pixel{j, row1}), get_value(pixel{j, row2}));
  std::swap(pivot_[row1], pivot_[row2]);
}

template <typename T>
inline void lu_decompose<T>::diagonalize(size_t row) {
  for (size_t i = row + 1; i < dimensions_; ++i) {
    decltype(auto) current = get_value(pixel{row, i});
    current /= get_value(pixel{row, row});
    for (size_t j = row + 1; j < dimensions_; ++j)
      get_value(pixel{j, i}) -= current * get_value(pixel{j, row});
  }
}

template <typename T>
inline algebra_vector<T> lu_decompose<T>::apply_pivot(
    const algebra_vector<T> &equal_to) {
  algebra_vector<T> pivoted(equal_to.size());

  for (size_t i = 0; i < pivot_.size(); ++i) {
    pivoted[i] = equal_to[pivot_[i]];
  }
  return move(pivoted);
}

template <typename T>
inline algebra_vector<T> lu_decompose<T>::forward_substitute(
    const algebra_vector<T> &equal_to) {
  algebra_vector<T> substitution(equal_to);

  for (size_t i = 0; i < dimensions_; ++i) {
    for (size_t j = 0; j < i; ++j) {
      substitution[i] -= get_value(pixel{j, i}) * substitution[j];
    }
  }
  return move(substitution);
}

template <typename T>
inline algebra_vector<T> lu_decompose<T>::back_substitute(
    const algebra_vector<T> &forward_substitution) {
  algebra_vector<T> substitution(forward_substitution);

  for (size_t i = 0; i < dimensions_; ++i) {
    auto r = dimensions_ - i - 1;
    for (size_t j = r + 1; j < dimensions_; ++j) {
      substitution[r] -= get_value(pixel{j, r}) * substitution[j];
    }
    substitution[r] /= get_value(pixel{r, r});
  }

  return move(substitution);
}

}  // namespace algebra::matrices