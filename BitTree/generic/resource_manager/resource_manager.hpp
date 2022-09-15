#pragma once

#include <memory_resource>

namespace tree::generic {

  class resource_manager final
  {
  public:
    explicit resource_manager(std::size_t capacity);
    void* allocate(std::size_t bytes);
    void deallocate(void* p, std::size_t bytes);
  private:    
    std::pmr::monotonic_buffer_resource buffer_;
  };

  extern resource_manager manager;
}
