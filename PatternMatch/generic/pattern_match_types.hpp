#pragma once

#include "generic/resource_manager/resource_manager.hpp"
#include <unordered_set>

namespace pattern_match{
  //pmr::vector and its resource allocator
  template<typename T>
  using pmr_hash_set = std::pmr::unordered_set<T>;
  
}