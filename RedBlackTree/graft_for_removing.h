#include "item_handle.hpp"

using namespace bbtree::item;

namespace bbtree::algorithm {

template <ComparableKey Key> 
static bool graft_for_removing(item_handle<Key> &parent);

} // namespace bbtree::algorithm