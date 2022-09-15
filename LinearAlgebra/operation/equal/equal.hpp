#pragma once

#include "equal.h"
#include "operation/utility.hpp"
#include <type_traits>
#include <cmath>

namespace algebra::arithmetic {

template <typename T>
inline bool are_equal(const algebra_vector<T> &left, const algebra_vector<T> &right) {
  ensure_match(left, right);
  if constexpr (std::is_floating_point_v<T>) 
    return std::abs((left - right).min()) < epsilon<T>;
  else
    return (left == right).min();
}

template <typename T>
inline bool operator==(const matrix<T> &left, const matrix<T> &right) {
  ensure_match(left, right);
  for (size_t i = 0U; i < left.columns(); ++i) {
    for (size_t j = 0U; j < left.rows(); ++j) {
      pixel id{i, j};      
      if constexpr (std::is_integral_v<T>) {
        if (left[id] != right[id]) return false;        
      } else {
        if (epsilon<T> <= std::abs(left[id] - right[id])) return false;
	  }
      
    }
  }
  return true;
}

}  // namespace algebra::arithmetic