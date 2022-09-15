#pragma once

#include <catch2/catch_test_macros.hpp>
#include "spin_lock/spin_lock.hpp"

namespace concurrent {
class shared_lock {
 public:
  shared_lock();
  void lock_shared();
  void unlock_shared();
  void lock();
  void unlock();
 private:
  spin_lock lock_;
  std::atomic_size_t shared_count_;
};

}  // namespace concurrent
