#pragma once

#include <memory>
#include "queue/atomic_item/atomic_item.hpp"
#include <valarray>

namespace concurrent {
template <typename T>
class queue final {
 public:
  queue(const size_t capacity);
  queue(const queue&) = delete;
  queue& operator=(const queue&) = delete;
  queue(queue&&) = delete;
  queue& operator=(queue&&) = delete;

  bool push(std::unique_ptr<T> input);
  bool pop(std::unique_ptr<T>& output);
  void wait_until_empty();

 private:
  size_t next_from_round_robin(std::atomic_size_t& ordinal);
  std::valarray<atomic_item> items_;
  std::atomic_size_t count_;
  std::atomic_size_t input_ordinal_;
  std::atomic_size_t output_ordinal_;
};

}  // namespace concurrent