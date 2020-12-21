#pragma once

#include "insert_graft.h"

using namespace bbtree::item;

namespace bbtree::algorithm {

template <ComparableKey Key>
static bool are_same_side(item_handle<Key> &parent, item_handle<Key> &child);

template <ComparableKey Key>
static bool are_opposite_side(item_handle<Key> &parent, item_handle<Key> &child);

template <ComparableKey Key>
static short get_side(item_handle<Key> &item);

template <ComparableKey Key>
inline void insert_graft(item_handle<Key> &parent, item_handle<Key> &child) {
  /*
  1. for black parent with one of child is red
  2.1 if the red child and parent has different status
      then child rotate
  2.2 then if the red child and parent has same status
      then parent rotate.
  */
  if (parent->color() == 0)
    return;

  if (parent->red_status() == item_status::children)
    parent->push_down_color();
  else {
    if (are_opposite_side(parent, child))
      child.rotate();
    if (are_same_side(parent, child))
      parent.rotate();
  }
}

template <ComparableKey Key>
bool are_same_side(item_handle<Key> &parent, item_handle<Key> &child) {
  if (auto parent_side = get_side(parent)) 
    return parent_side == get_side(child);
  return false;
  
}

template <ComparableKey Key>
bool are_opposite_side(item_handle<Key> &parent, item_handle<Key> &child) {
  if (auto parent_side = get_side(parent))
    return parent_side + get_side(child) == 0;
  return false;
}

template <ComparableKey Key> short get_side(item_handle<Key> &item) {
  switch (item->red_status()) {
  case item_status::lchild:
    return -1;
  case item_status::rchild:
    return 1;
  default:
    return 0;
  }
}

} // namespace bbtree::algorithm