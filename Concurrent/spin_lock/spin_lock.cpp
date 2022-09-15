#include "spin_lock.hpp"

namespace concurrent {
spin_lock::spin_lock(bool guard) {
  if (guard) guard_.test_and_set(std::memory_order_acquire);
}
bool spin_lock::try_lock() {
  return !guard_.test_and_set(std::memory_order_acquire);
}
void spin_lock::lock() {
  while (guard_.test_and_set(std::memory_order_acquire))
	  ;
}
void spin_lock::unlock() { guard_.clear(std::memory_order_release); }
}  // namespace concurrent