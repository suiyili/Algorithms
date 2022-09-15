#include "generic/utility.hpp"
#include <utility>

using namespace generic;

namespace sort_algo {

template<RandomAccessIterator Iterator> class heap final {
public:
  using size_type_t = typename std::iterator_traits<Iterator>::difference_type;

  heap(Iterator begin, Iterator end, compare_func <Iterator> compare);
  ~heap() = default;

  heap(const heap &) = delete;
  heap(heap &&) = delete;

  auto pop_top();
  auto size() const;

private:

  void sink(size_type_t parent);
  bool compare(size_type_t left, size_type_t right) const;
  void swap(size_type_t left, size_type_t right);
  Iterator get_iter(size_type_t pos) const;

  Iterator begin_;
  size_type_t size_;
  compare_func <Iterator> compare_;
};
template<RandomAccessIterator Iterator>
heap(Iterator
begin,
Iterator end, compare_func<Iterator>
compare)
->
heap<Iterator>;

} // namespace sort_algo::heapsort
