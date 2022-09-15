#pragma once

#include "priority_queue.h"
#include "generic/resource_manager/resource_manager.hpp"
#include <utility>

namespace graph::generic {
template <comparable T>
inline priority_queue<T>::priority_queue() noexcept
    : heap_(resource_manager::get_allocator<T *>()),
      indices_(resource_manager::get_allocator<
               std::pair<const T *const, std::size_t>>()) {}

template <comparable T>
inline void priority_queue<T>::push(T *key) noexcept {
  auto id = append(key);
  swim(id);
}

template <comparable T> inline T *priority_queue<T>::pop() noexcept {
  auto top = remove_top();
  sink(0);
  return top;
}

template <comparable T>
inline void graph::generic::priority_queue<T>::update(T *key) noexcept {
  auto found = indices_.find(key);
  if (found != indices_.end()) {
    if (!swim(found->second))
      sink(found->second);
  }
}

template <comparable T>
inline std::size_t priority_queue<T>::append(T *key) noexcept {
  auto id = heap_.size();
  heap_.push_back(key);
  indices_.emplace(key, id);
  return id;
}

template <comparable T>
inline bool priority_queue<T>::swim(std::size_t id) noexcept {
  auto child = id, parent = id;
  do {
    child = parent;
    parent = find_parent(child);
  } while (compare_exchange(child, parent));
  return child < id;
}

template <comparable T>
inline bool priority_queue<T>::sink(std::size_t id) noexcept {
  auto top_child = id, parent = id;
  do {
    parent = top_child;
    top_child = find_top_child(parent);
  } while (parent < top_child && compare_exchange(top_child, parent));
  return id < parent;
}

template <comparable T>
inline T *priority_queue<T>::remove_top() noexcept {
  T *top = nullptr;
  if (!heap_.empty()) {
    top = heap_.front();
    if (auto last = heap_.size() - 1; last > 0)
      exchange(0, last);
    heap_.pop_back();
    indices_.erase(top);
  }
  return top;
}

template <comparable T>
inline bool priority_queue<T>::compare_exchange(std::size_t lhs,
                                                std::size_t rhs) noexcept {

  auto less = compare(lhs, rhs);
  if (less)
    exchange(lhs, rhs);

  return less;
}

template <comparable T>
inline bool priority_queue<T>::compare(std::size_t lhs,
                                       std::size_t rhs) noexcept {
  auto& lhs_key = heap_[lhs];
  auto& rhs_key = heap_[rhs];

  auto comp = (*lhs_key) <=> (*rhs_key);
  return comp < 0;
}

template <comparable T>
inline void priority_queue<T>::exchange(std::size_t lhs,
                                        std::size_t rhs) noexcept {
  auto& lhs_key = heap_[lhs];
  auto& rhs_key = heap_[rhs];
  std::swap(lhs_key, rhs_key);
  std::swap(indices_[rhs_key], indices_[lhs_key]);
}

template <comparable T>
inline std::size_t priority_queue<T>::find_parent(std::size_t child) noexcept {
  return child == 0 ? 0 : (child - 1) / 2;
}

template <comparable T>
inline std::size_t
priority_queue<T>::find_top_child(std::size_t parent) noexcept {
  auto [left_child, right_child] = get_children(parent);
  auto top_child = parent;
  if (left_child < heap_.size())
    top_child = left_child;
  if (right_child < heap_.size() && compare(right_child, left_child))
    top_child = right_child;
  return top_child;
}

template <comparable T>
inline std::pair<std::size_t, std::size_t>
priority_queue<T>::get_children(std::size_t parent) noexcept {
  decltype(parent) left_child = parent * 2 + 1, right_child = left_child + 1;
  return std::make_pair(left_child, right_child);
}

} // namespace graph::generic