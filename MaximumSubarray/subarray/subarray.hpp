#pragma once

#include "subarray.h"
#include "utility.hpp"

namespace generic {
template <typename ITER>
inline subarray<ITER>::subarray(ITER begin, ITER end)
    : begin_(begin), end_(end), sum_(sum(begin, end)) {}

template <typename ITER>
inline subarray<ITER>::subarray(const subarray &other)
    : begin_(other.begin_), end_(other.end_), sum_(other.sum_) {}

template <typename ITER> inline const ITER &subarray<ITER>::begin() const {
  return begin_;
}

template <typename ITER> inline const ITER &subarray<ITER>::end() const {
  return end_;
}

template <typename ITER> inline auto subarray<ITER>::sum() const {
  return sum_;
}

template <typename ITER> inline auto subarray<ITER>::sum(ITER begin, ITER end) {
  return std::accumulate<ITER, value_type>(begin, end,
                                           neutral_value<value_type>);
}

} // namespace maximum_subarray
