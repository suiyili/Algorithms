#include "support.hpp"

namespace sortalgo::heapsort {
template <typename ITER>  
void heap_sort(ITER begin, ITER end, compare_func<ITER> comp);
} // namespace sortalgo::heapsort