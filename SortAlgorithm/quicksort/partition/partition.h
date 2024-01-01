#include "generic/utility.hpp"
#include <utility>
#include <ranges>

using namespace generic;

namespace sort_algo {

template<std::ranges::forward_range range_t_>
std::ranges::iterator_t<range_t_> make_partition(range_t_& sequence);

template <RandomAccessIterator Iterator> class partitioner {
public:
  partitioner(Iterator begin, Iterator end, compare_func<Iterator> comp);
  auto get_front() const noexcept;
  auto get_back() const noexcept;
private:
  static void swap(Iterator i, Iterator j);
  Iterator front_;
  Iterator back_;
  compare_func<Iterator> comp_;
};

template <RandomAccessIterator Iterator>
partitioner(Iterator begin, Iterator end, compare_func<Iterator> comp)
    ->partitioner<Iterator>;

} // namespace sort_algo::quicksort