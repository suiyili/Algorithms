#pragma once

#include "heap.hpp"
#include "heap_sort.h"

namespace sortalgo::heapsort {
template <typename ITER>
inline void heap_sort(ITER begin, ITER end, compare_func<ITER> comp) {
  heap h(begin, end, comp);
  while (h.pop_top() != begin)
    ;
}
} // namespace sortalgo::heapsort