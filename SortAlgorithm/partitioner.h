#include "support.hpp"
#include <utility>

namespace sortalgo::quicksort {

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

} // namespace sortalgo::quicksort