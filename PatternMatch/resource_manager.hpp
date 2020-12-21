#pragma once

#include <memory_resource>

namespace pattern_match {
class resource_manager final {
 public:
  explicit resource_manager(size_t capacity);
  template<typename T>
  auto get_allocator()
  {
    static resource_manager resource(4096);
    return std::pmr::polymorphic_allocator<T>(&resource.buffer_);
  }
 private:
  std::pmr::monotonic_buffer_resource buffer_;
  std::pmr::unsynchronized_pool_resource pool_;
};

}  // namespace pattern_match