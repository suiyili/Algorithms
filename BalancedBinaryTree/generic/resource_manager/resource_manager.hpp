#pragma once

#include <memory_resource>
#include <cstdlib>

namespace btree::generic {
class resource_manager {
public:
  static void *allocate(std::size_t size);
  static void deallocate(void *p, std::size_t size);

private:
  static std::pmr::monotonic_buffer_resource buffer_;
};

} // namespace btree::generic
