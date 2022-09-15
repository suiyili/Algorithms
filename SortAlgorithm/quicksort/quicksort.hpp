#pragma once
#include "quicksort.h"
#include "quicksort/partitioner/partitioner.hpp"
#include <forward_list>

namespace sort_algo {

template <typename Iterator>
using domain = std::pair<Iterator, Iterator>;

template <RandomAccessIterator Iterator>
inline void quicksort(Iterator begin, Iterator end, compare_func<Iterator> comp) {
  std::forward_list<domain<Iterator>> stack;
  stack.emplace_front(begin, end);

  while (!stack.empty()) {
    auto front = stack.front();
    stack.pop_front();
    partitioner partition(front.first, front.second, comp);
    if (front.first != partition.get_front())
      stack.emplace_front(front.first, partition.get_front());
    if (front.second != partition.get_back())
      stack.emplace_front(partition.get_back(), front.second);
  }
}
}