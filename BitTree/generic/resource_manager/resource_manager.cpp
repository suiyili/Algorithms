#include "resource_manager.hpp"

namespace tree::generic {

  resource_manager::resource_manager(std::size_t capacity)
    :buffer_(capacity) {}

  void* resource_manager::allocate(std::size_t bytes)
  {
    return buffer_.allocate(bytes);
  }
  void resource_manager::deallocate(void* p, std::size_t bytes)
  {
    buffer_.deallocate(p, bytes);
  }

  resource_manager manager(4096U);
}