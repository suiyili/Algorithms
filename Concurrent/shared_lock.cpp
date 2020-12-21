#include "shared_lock.hpp"
#include <mutex>

namespace concurrent {
shared_lock::shared_lock() : shared_count_(0U) {}

void shared_lock::lock_shared() {
  std::lock_guard<spin_lock> guard(lock_);
  ++shared_count_;
}

void shared_lock::unlock_shared() { --shared_count_; }

void shared_lock::lock() {
  lock_.lock();
  while (shared_count_.load(std::memory_order_relaxed) > 0U)
    ;
}

void shared_lock::unlock() { lock_.unlock(); }
}  // namespace concurrent
