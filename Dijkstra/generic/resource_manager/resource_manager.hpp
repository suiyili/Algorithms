#pragma once

#include <memory_resource>

namespace graph::generic {
  class resource_manager
  {
  public:

    template<typename T>
    static auto get_allocator()
    {
      static resource_manager resource(4096);
      return std::pmr::polymorphic_allocator<T>(&resource.buffer_);
    }

  private:
    explicit resource_manager(std::size_t capacity);
    std::pmr::monotonic_buffer_resource buffer_;
  };
}
