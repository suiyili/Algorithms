#pragma once

#include "find_maximum_subarray.h"
#include "utility.hpp"

namespace maximum_subarray {
template <typename ITER>
subarray<ITER> find_maximum_subarray(ITER begin, ITER end) {

  /*
  1. max_subarray(i) means a max subarray ended on item[i]
  2. max_subarray(i) = max(item[i], item[i] + max_subarray(i-1))
  3. iterate each item for its max_subarray, find global max one.
  */
  using subarray_t = subarray<ITER>;
  using value_type_t = typename subarray_t::value_type;

  if (begin == end) {
    throw std::length_error("input has at least one item!");
  }

  auto cursor = begin + 1;

  auto current = std::make_shared<subarray_t>(begin, cursor);
  auto maximum = current;

  while (end != cursor) {
    auto current_start = current->sum() < neutral_value<value_type_t>
                             ? cursor
                             : current->begin();
    auto current_end = cursor + 1;

    current = std::make_shared<subarray_t>(current_start, current_end);

    if (current->sum() > maximum->sum())
      maximum = current;

    cursor = current_end;
  }
  return *maximum;
}
} // namespace maximum_subarray