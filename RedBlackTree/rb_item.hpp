#pragma once

#include "color_error.hpp"
#include "rb_item.h"

namespace bbtree::item {

template <ComparableKey Key>
inline rb_item<Key>::rb_item(std::unique_ptr<Key> key)
    : key_(std::move(key)), color_(0U), left(nullptr), right(nullptr) {}

template <ComparableKey Key> 
inline Key &rb_item<Key>::get_key() { return *key_; }

template <ComparableKey Key>
inline std::unique_ptr<Key> rb_item<Key>::release_key() {
  return std::unique_ptr<Key>(key_.release());
}

template <ComparableKey Key> 
inline generical::byte rb_item<Key>::color() const {
  return color_;
}

template <ComparableKey Key> 
inline item_status rb_item<Key>::red_status() const {

  /*
   1. null is black.
   2. red item should only connect from/to black, no two red should be connected.
  */
  generical::byte children_red = check_red(left) ? 1U : 0U;
  children_red += check_red(right) ? 2U : 0U;

  switch (children_red) {
  case 0U: //both children black
    if (color_ == 0)
      return item_status::parent;
    else
      return item_status::none;
  case 1U: //left is red
    return item_status::lchild;
  case 2U: //right child is red
    return item_status::rchild;
  case 3U: //both children red
    if (color_ > 0)
      return item_status::children;
    break;
  }
  throw color_error("the color is wrong");
}

template <ComparableKey Key>
inline bool rb_item<Key>::check_red(rb_item<Key> *item) const {
  return item && item->color() == 0;
}

template <ComparableKey Key> 
inline void rb_item<Key>::increase_color() { ++color_; }

template <ComparableKey Key> 
inline void rb_item<Key>::pull_up_color() {
  generical::byte dummy = 2U;
  generical::byte &left_color = get_color(left, dummy);
  generical::byte &right_color = get_color(right, dummy);

  if (left_color == 0 || right_color == 0)
    throw color_error("no color can be pulled up");

  --left_color;
  --right_color;
  ++color_;
  return;
}

template <ComparableKey Key> 
inline void rb_item<Key>::push_down_color() {
  if (color_ == 0)
    throw color_error("no color can be pushed down");
  generical::byte dummy = 0U;
  decltype(auto) left_color = get_color(left, dummy);
  decltype(auto) right_color = get_color(right, dummy);
  ++left_color;
  ++right_color;
  --color_;
  return;
}

template <ComparableKey Key>
inline generical::byte &rb_item<Key>::get_color(rb_item<Key> *child,
                                           generical::byte &dummy) {
  return child == nullptr ? dummy : child->color_;
}

template <ComparableKey Key>
inline void swap_value(rb_item<Key> &left, rb_item<Key> &right) {
  left.key_.swap(right.key_);
}

} // namespace bbtree::item
