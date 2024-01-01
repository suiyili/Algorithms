#pragma once
#include "partition.h"
#include <stdexcept>

namespace sort_algo {

template<std::ranges::forward_range range_t_>
inline std::ranges::iterator_t<range_t_> make_partition(range_t_& sequence) {
  /*
   * partition iter pi start from rbegin(end), front iter fi start begin.
   * 1 if pi.base() == fi, then exit loop
   * 2 if item[pi] >= item[last], move pi one step
   * 3 otherwise swap item[pi] with item[fi] and move fi one step
  */
  auto front = sequence.begin();
  auto partition = std::make_reverse_iterator(sequence.end());
  auto last = partition;
  while(front != partition.base()) {
    if(*partition < *last) {
      std::swap(*partition, *front);
      ++front;
    } else
      ++partition;
  }
  return partition.base();
}

template <RandomAccessIterator Iterator>
inline partitioner<Iterator>::partitioner(Iterator begin, Iterator end,
                                          compare_func<Iterator> comp) 
: front_(begin), back_(end), comp_(comp){
  /*
  1. last element as partition value, li as iterator
  2. partition iterator pi: item[i < pi] < item[li] <= item[i >= pi]
  3. front runner iterator fi, 
     loop: pi <= fi < li
       if comp(item[fi], item[li] )
         if pi < fi then swap(item[fi], item[pi])
         pi++
  4. if pi < li, swap(item[pi], item[li])
  */
  auto dist = std::distance(begin, end);
  if (dist == 0)
    throw std::invalid_argument("range is empty");
  else if (dist > 1) {
    auto last = end - 1;
    auto partition = begin;
    for (auto i = begin; i != last; ++i) {
      if (comp_(*i, *last)) {
        swap(partition, i);
        ++partition;
      }
    }
    swap(partition, last);
    front_ = partition;
    back_ = front_ + 1;
  }    
}
template <RandomAccessIterator Iterator>
inline auto partitioner<Iterator>::get_front() const noexcept {
  return front_;
}
template <RandomAccessIterator Iterator>
inline auto partitioner<Iterator>::get_back() const noexcept {
  return back_;
}
template <RandomAccessIterator Iterator>
inline void partitioner<Iterator>::swap(Iterator i, Iterator j) {
  if (i != j)
    std::swap(*i, *j);
}
} // namespace sort_algo::quicksort