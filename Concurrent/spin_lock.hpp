#pragma once

#include <atomic>

namespace concurrent {
class spin_lock final {
 public:
  explicit spin_lock(bool guard = false);
  spin_lock(const spin_lock&) = delete;
  spin_lock& operator=(const spin_lock&) = delete;
  spin_lock(spin_lock&&) = delete;
  spin_lock& operator=(spin_lock&&) = delete;

  bool try_lock();
  void lock();
  void unlock();

 private:
  std::atomic_flag guard_ = ATOMIC_FLAG_INIT;
};

}  // namespace concurrent