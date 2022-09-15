#pragma once

#include <memory_resource>

namespace pattern_match {
class resource_manager final {
 public:
  template <typename T>
  static auto get_allocator() {
    static resource_manager resource(4096);
    return std::pmr::polymorphic_allocator<T>(&resource.pool_);
  }

 private:
  explicit resource_manager(size_t capacity);
  std::pmr::monotonic_buffer_resource buffer_;
  std::pmr::unsynchronized_pool_resource pool_;
};

}  // namespace pattern_match