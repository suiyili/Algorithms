#pragma once

#include "item_handle.h"
#include "item_not_exists.hpp"
#include "rotate_error.hpp"

namespace bbtree::item {

template <ComparableKey Key>
inline item_handle<Key>::item_handle(rb_item<Key> *&item) : item_(item) {}

template <ComparableKey Key>
inline item_handle<Key>::item_handle(const item_handle<Key> &other)
    : item_(other.item_) {}

template <ComparableKey Key>
inline item_handle<Key>::item_handle(item_handle<Key> &&other)
    : item_(other.item_) {}

template <ComparableKey Key> 
inline void item_handle<Key>::rotate() {
  /*
  1. each branch from top to leaf should has equal number of black.
  2. rotate only happens if two children has different color, parent could be any color.
  3. both position and color should be swapped between child and parent 
  */
  check(item_);

  switch (item_->red_status()) {
  case item_status::lchild:
    left_rotate();
    break;
  case item_status::rchild:
    right_rotate();
    break;
  default:
    throw rotate_error("can not do rotate");
  }
  return;
}

template <ComparableKey Key> 
inline void item_handle<Key>::left_rotate() {
  auto left_child = item_->left;

  left_child->color_ = item_->color_;
  item_->color_ = 0;

  item_->left = left_child->right;
  left_child->right = item_;
  item_ = left_child;

  return;
}

template <ComparableKey Key> 
inline void item_handle<Key>::right_rotate() {
  auto right_child = item_->right;

  right_child->color_ = item_->color_;
  item_->color_ = 0;

  item_->right = right_child->left;
  right_child->left = item_;
  item_ = right_child;

  return;
}

template <ComparableKey Key> 
inline item_handle<Key>::operator bool() const {
  return item_ != nullptr;
}

template <ComparableKey Key>
inline rb_item<Key> *item_handle<Key>::operator->() {
  check(item_);
  return item_;
}

template <ComparableKey Key> 
inline rb_item<Key> &item_handle<Key>::operator*() {
  check(item_);
  return *item_;
}

template <ComparableKey Key> 
inline rb_item<Key> *item_handle<Key>::set(rb_item<Key> *item) {
  auto released = item_;
  item_ = item;
  return released;
}

template <ComparableKey Key> 
inline rb_item<Key> *item_handle<Key>::release() {
  return set(nullptr);
}

template <ComparableKey Key> 
inline void item_handle<Key>::check(rb_item<Key> *item) {
  if (item == nullptr)
    throw item_not_exists("the item is null");
}

} // namespace bbtree::item