#pragma once

#include "heapsort/heap/heap.hpp"
#include "heapsort.h"

namespace sort_algo {
template <typename ITER>
inline void heapsort(ITER begin, ITER end, compare_func<ITER> comp) {
  heap h(begin, end, comp);
  while (h.pop_top() != begin)
    ;
}
} // namespace sort_algo::heapsort