#pragma once

#include "priority_queue.h"
#include "resource_manager.hpp"
#include <utility>

namespace graph::generic {
template <typename T>
requires comparable<T> inline priority_queue<T>::priority_queue() noexcept
    : heap_(resource_manager::get_allocator<T *>()),
      indices_(resource_manager::get_allocator<
               std::pair<const T *const, std::size_t>>()) {}

template <typename T>
requires comparable<T> inline void
priority_queue<T>::push(const T *key) noexcept {
  auto id = append(key);
}

template <typename T>
requires comparable<T> inline const T *priority_queue<T>::pop() noexcept {
  return nullptr;
}

template <typename T>
requires comparable<T> inline void
graph::generic::priority_queue<T>::update(const T *key) noexcept {}

template <typename T>
requires comparable<T> inline std::size_t
priority_queue<T>::append(const T *key) {
  auto id = heap_.size();
  heap_.push_back(key);
  indices_.emplace(key, id);
  return id;
}

template <typename T>
requires comparable<T> inline void priority_queue<T>::swim(std::size_t id) {
  auto child = id, parent = id;
  do {
    child = parent;
    parent = find_parent(child);
  } while (compare_exchange(child, parent));
}

template <typename T>
requires comparable<T> inline bool
priority_queue<T>::compare_exchange(std::size_t lhs, std::size_t rhs) {
  decltype(auto) lhs_key = heap_[lhs];
  decltype(auto) rhs_key = heap_[rhs];

  auto less = (*lhs_key) < (*rhs_key);
  if (less) {
    std::swap(lhs_key, rhs_key);
    std::swap(indices_[rhs_key], indices_[lhs_key]);
  }
  return less;
}

template <typename T>
requires comparable<T> inline std::size_t
priority_queue<T>::find_parent(std::size_t child) {
  return child == 0 ? 0 : (child - 1) / 2;
}

} // namespace graph::generic