#pragma once

#include "queue.h"

namespace concurrent {
template <typename T>
inline queue<T>::queue(const size_t capacity)
    : items_(capacity), count_(0U), input_ordinal_(0U), output_ordinal_(0U) {}

template <typename T> inline bool queue<T>::push(std::unique_ptr<T> input) {
  if (!input)
    return false;

  size_t i = next_from_round_robin(input_ordinal_);
  auto put = items_[i].put(input.get());
  if (put) {
    ++count_;
    input.release();
  }
  return put;
}

template <typename T> inline bool queue<T>::pop(std::unique_ptr<T> &output) {
  void *item = nullptr;
  size_t i = next_from_round_robin(output_ordinal_);
  auto taken = items_[i].take(item);
  if (taken) {
    --count_;
    output.reset(static_cast<T *>(item));
  }
  return taken;
}

template <typename T> inline void queue<T>::wait_until_empty() {
  while (count_.load(std::memory_order_relaxed) > 0U)
    ;
}

template <typename T>
inline size_t queue<T>::next_from_round_robin(std::atomic_size_t &ordinal) {
  auto current = ordinal.load(std::memory_order_relaxed);
  decltype(current) next = 0U;
  do {
    next = current + 1U;
    if (next == items_.size())
      next = 0U;
  } while (!ordinal.compare_exchange_strong(
      current, next, std::memory_order_release, std::memory_order_relaxed));
  return next;
}

} // namespace concurrent