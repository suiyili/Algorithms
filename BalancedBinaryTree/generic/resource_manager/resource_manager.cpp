#include "resource_manager.hpp"

namespace btree::generic {

std::pmr::monotonic_buffer_resource resource_manager::buffer_ =
    std::pmr::monotonic_buffer_resource(4096U);

void *resource_manager::allocate(std::size_t size) {
  return buffer_.allocate(size);
}

void resource_manager::deallocate(void *p, std::size_t size) {
  buffer_.deallocate(p, size);
}
} // namespace btree::generic