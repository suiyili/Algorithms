#include "item_handle.hpp"

using namespace bbtree::item;

namespace bbtree::algorithm {

template <ComparableKey Key>
void insert_graft(item_handle<Key> &parent, item_handle<Key> &child);
} // namespace bbtree::algorithm