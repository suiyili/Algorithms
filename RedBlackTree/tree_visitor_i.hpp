#pragma once

#include "item_handle.hpp"
#include <forward_list>

using namespace bbtree::item;

namespace bbtree {

template<ComparableKey Key>
class tree_visitor_i {
public:
  virtual ~tree_visitor_i() = default;
  virtual void visit(item_handle<Key> &root) = 0;
};

template <ComparableKey Key>
using branch_t = std::forward_list<item_handle<Key>>;

} // namespace bbtree