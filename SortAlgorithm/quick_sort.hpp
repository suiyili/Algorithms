#pragma once
#include "quick_sort.h"
#include "partitioner.hpp"
#include <forward_list>

namespace sortalgo::quicksort {

template <typename Iterator>
using domain = std::pair<Iterator, Iterator>;

template <RandomAccessIterator Iterator>
inline void quick_sort(Iterator begin, Iterator end, compare_func<Iterator> comp) {
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