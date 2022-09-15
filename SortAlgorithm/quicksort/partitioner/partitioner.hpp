#pragma once
#include "partitioner.h"
#include <stdexcept>

namespace sort_algo {
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