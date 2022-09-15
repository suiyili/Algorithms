#pragma once

#include "heapsort/heap/heap.h"
#include <stdexcept>

namespace sort_algo {

template <RandomAccessIterator Iterator>
inline heap<Iterator>::heap(Iterator begin, Iterator end,
                            compare_func<Iterator> compare)
    : begin_(begin), size_(std::distance(begin, end)), compare_(compare) {
  /*
      make the top one max.
      1.set up binary(or tri-nary) tree bottom-up
      2.start from middle which is the parent of the bottom child.
      3.parent reversely compare(if '<' provided, get '!<') with all its
     children. 4.swap the top(max one if compare is '<') with the bottom item
     and pop it.
   */
  if (size_ == 0)
    throw std::invalid_argument("no value found");
  decltype(size_) middle = size_ / 2;

  for (decltype(middle) i = 0; i <= middle; ++i)
    sink(middle - i);
}

template <RandomAccessIterator Iterator>
inline auto heap<Iterator>::pop_top() {
  /*
  1. swap the top item[0] with the last item
  2. shrink size_ one position. hold it for return.
  3. sink the new top.
  */
  if (size_ == 1)
    return begin_;
 
  auto &last = size_;
  swap(0, --last);  
  sink(0);
  return get_iter(last);
}

template <RandomAccessIterator Container>
inline auto heap<Container>::size() const {
  return size_;
}

template <RandomAccessIterator Iterator>
inline bool heap<Iterator>::compare(size_type_t left, size_type_t right) const{
  auto it_left = get_iter(left);
  auto it_right = get_iter(right);

  return compare_(*it_left, *it_right);
}

template <RandomAccessIterator Iterator>
inline void heap<Iterator>::swap(size_type_t left, size_type_t right) {
  auto it_left = get_iter(left);
  auto it_right = get_iter(right);
  std::swap(*it_left, *it_right);
}

template <RandomAccessIterator Iterator>
inline Iterator heap<Iterator>::get_iter(size_type_t pos) const {
  auto i = begin_;
  std::advance(i, pos);
  return i;
}

template <RandomAccessIterator Iterator>
inline void heap<Iterator>::sink(size_type_t parent) { 
   
  auto sink = true;
  while (sink) {
    sink = false;
    auto left_child = (parent << 1) + 1;
    auto right_child = left_child + 1;

    if (left_child < size_) {
      auto selected = left_child;
      if (right_child < size_) {
        if (compare(selected, right_child))
          selected = right_child;        
      }
      if (compare(parent, selected)) {
        swap(parent, selected);
        parent = selected;
        sink = true;
      }        
    }
  }
  
}

/*
template <typename ITER>
inline heap<ITER>::heap(ITER begin, ITER cursor, ITER end)
    : begin_(begin), cursor_(cursor), end_(end) {

  auto length = std::distance(begin, end);
  auto middle = begin;
  std::advance(middle, length / 2);

  auto rmiddle = std::make_reverse_iterator(middle);
  auto rend = std::make_reverse_iterator(begin);

  for (auto i = rmiddle; i != rend; ++i) {
    auto cur = i.base();
    heap_cursor_t cursor(begin, --cur, end);
    while (cursor.sink(comp_))
      ;
  }
}

template <typename ITER> inline bool heap<ITER>::sink(compare_func<ITER> comp) {
  auto selected_child = find_max_child(comp);
  if (selected_child != cursor_) {
    if (comp(*selected_child, *cursor_)) {
      std::swap(*cursor_, *selected_child);
      cursor_ = selected_child;
      return true;
    }
  }

  return false;
}

template <typename ITER>
inline ITER heap<ITER>::find_max_child(compare_func<ITER> comp) const {
  auto length = std::distance(begin_, end_);

  auto diff = std::distance(begin_, cursor_);
  auto left = (diff << 1U) + 1U;

  auto selected_child = cursor_;
  if (left < length) {
    selected_child = begin_ + left;
    auto right = left + 1U;
    if (right < length) {
      auto right_cur = std::next(selected_child);
      if (comp(*right_cur, *selected_child)) {
        selected_child = right_cur;
      }
    }
  }

  return selected_child;
}*/

} // namespace sort_algo::heapsort