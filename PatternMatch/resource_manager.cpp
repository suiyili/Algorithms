#include "resource_manager.hpp"

namespace pattern_match {
resource_manager::resource_manager(size_t capacity)
:buffer_(capacity), pool_(&buffer_)
{}
}  // namespace pattern_match