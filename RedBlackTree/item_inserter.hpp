#pragma once

#include "insert_graft.hpp"
#include "item_already_exists.hpp"
#include "item_inserter.h"

namespace bbtree::algorithm {

template <ComparableKey Key>
inline item_inserter<Key>::item_inserter(std::unique_ptr<Key> key)
    : to_insert_(std::move(key)) {}

template <ComparableKey Key>
inline item_inserter<Key>::item_inserter(item_inserter<Key> &&other) noexcept
    : to_insert_(std::move(other.to_insert_)) {}

template <ComparableKey Key>
inline void item_inserter<Key>::visit(item_handle<Key> &root) {
  auto branch = find_insert_branch(root);
  insert_into(std::move(branch));
}

template <ComparableKey Key>
inline branch_t<Key>
item_inserter<Key>::find_insert_branch(item_handle<Key> &root) {
  branch_t<Key> branch_stack;

  decltype(auto) key = *to_insert_;
  branch_stack.push_front(root);

  while (branch_stack.front()) {
    decltype(auto) top = *branch_stack.front();
    if (key < top.get_key())
      branch_stack.emplace_front(top.left);
    else if (top.get_key() < key)
      branch_stack.emplace_front(top.right);
    else
      throw item_already_exists("item already exists");
  }
  return std::move(branch_stack);
}

template <ComparableKey Key>
inline void item_inserter<Key>::insert_into(branch_t<Key> branch) {
  auto child = std::make_unique<item_handle<Key>>(branch.front());
  branch.pop_front();
  child->set(new rb_item(std::move(to_insert_)));
  // handle color
  while (!branch.empty()) {
    insert_graft(branch.front(), *child);
    child = std::make_unique<item_handle<Key>>(branch.front());
    branch.pop_front();
  }
}
} // namespace bbtree::algorithm