#include "generic/utility.hpp"

using namespace generic;
namespace sort_algo {
template <RandomAccessIterator Iterator>
void quicksort(Iterator begin, Iterator end, compare_func<Iterator> comp);
}