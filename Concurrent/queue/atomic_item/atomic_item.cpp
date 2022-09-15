#include "atomic_item.hpp"

namespace concurrent {
bool atomic_item::put(void* item) {
  void* temp = nullptr;
  return item_.compare_exchange_weak(temp, item, std::memory_order_release,
                                     std::memory_order_relaxed);
}

bool atomic_item::take(void*& item) {
  void* temp = nullptr;
  while (!item_.compare_exchange_weak(temp, nullptr, std::memory_order_release,
                                      std::memory_order_relaxed))
    ;
  item = temp;
  return temp != nullptr;
}
}  // namespace concurrent
