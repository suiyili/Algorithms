#include "generic/utility.hpp"

using namespace generic;

namespace sort_algo {
template <typename ITER>  
void heapsort(ITER begin, ITER end, compare_func<ITER> comp);
} // namespace sort_algo::heapsort