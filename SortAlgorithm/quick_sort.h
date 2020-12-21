#include "support.hpp"

namespace sortalgo::quicksort {
template <RandomAccessIterator Iterator>
void quick_sort(Iterator begin, Iterator end, compare_func<Iterator> comp);
}