#pragma once

#include "graft_for_removing.h"
#include <forward_list>

namespace bbtree::algorithm {

template <ComparableKey Key> static bool is_red(item_handle<Key> &item);

template <ComparableKey Key> static item_status get_xchild_side(item_handle<Key> &parent);

template <ComparableKey Key> static item_handle<Key> get_child(rb_item<Key>& item, item_status side);

static item_status sibling_side_of(item_status side);

template <ComparableKey Key>
static void rotate_sibling(item_handle<Key> &parent, item_status x_side);

template <ComparableKey Key>
inline bool graft_for_removing(item_handle<Key> &parent) {

  // sibling is the opposide of the x_item (color==2)
  // keep the handle of the origin parent.
  // Recursively rotating the parent sibling side item if it is red.
  // when it is black, then call rotate_sibling.
  // suppose pull_up_color called in rotate_sibling,
  // it will stop that color==2 then pull color up,
  // since one of parent in stack must be the red sibling before rotating.

  auto x_side = get_xchild_side(parent);  
  if (x_side == item_status::none)
    return false;

  auto sibling_side = sibling_side_of(x_side);

  std::forward_list<std::decay_t<decltype(parent)>> branch;
  branch.push_front(parent);

  while (is_red(get_child(*branch.front(), sibling_side))) {
    branch.front().rotate();
    branch.push_front(get_child(*branch.front(), x_side));
  }

  while (!branch.empty()) {
    rotate_sibling(branch.front(), x_side);
    if (branch.front()->color() > 1)
      branch.pop_front();
    else
      branch.clear();
  }

  return true;
}

template <ComparableKey Key> inline bool is_red(item_handle<Key> &item) {
  return item && item->color() == 0;
}

template <ComparableKey Key>
item_status get_xchild_side(item_handle<Key> &parent) {
  auto left = parent->left;
  auto right = parent->right;
  item_status x_side = item_status::none;

  if (left != nullptr && left->color() > 1U)
    x_side = item_status::lchild;
  else if (right != nullptr && right->color() > 1U)
    x_side = item_status::rchild;

  return x_side;
}

template <ComparableKey Key>
item_handle<Key> get_child(rb_item<Key> &item, item_status side) {
  switch (side) {  
  case bbtree::item_status::lchild:
    return item.left;
  case bbtree::item_status::rchild:
    return item.right;  
  default:
    throw std::logic_error("must be left or right child status");
  }
}

template <ComparableKey Key>
inline void rotate_sibling(item_handle<Key> &parent, item_status x_side) {
    
  //in this stage sibling is either black or null.
  auto sibling = get_child(*parent, sibling_side_of(x_side));
  decltype(auto) parent_item = *parent;

  if (sibling) {
    auto nephew_status = sibling->red_status();
    if (nephew_status != item_status::none){
      if (nephew_status == x_side)
        sibling.rotate();
      sibling->push_down_color();      
      parent.rotate();
    }
  }
  parent_item.pull_up_color();
}

inline item_status sibling_side_of(item_status side) {
  switch (side) {
  case bbtree::item_status::lchild:
    return item_status::rchild;
  case bbtree::item_status::rchild:
    return item_status::lchild;
  default:
    throw std::logic_error("only lchild or rchild are supported!");
  }
}

} // namespace bbtree::algorithm