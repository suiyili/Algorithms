#pragma once

#include <atomic>

namespace concurrent {
class atomic_item final {
 public:
  atomic_item() = default;
  ~atomic_item() = default;

  atomic_item(const atomic_item&) = delete;
  atomic_item& operator=(const atomic_item&) = delete;
  atomic_item(atomic_item&&) = delete;
  atomic_item& operator=(atomic_item&&) = delete;

  bool put(void* item);
  bool take(void*& item);

 private:
  std::atomic<void*> item_ = nullptr;
};

}  // namespace concurrent