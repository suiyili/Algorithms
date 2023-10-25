#pragma once

#include <generic/error_type.hpp>
#include "rb_node.h"
#include <generic/resource_manager/resource_manager.hpp>

namespace btree::node {

inline side opposite(side which) {
  return which == side::left ? side::right : side::left;
}

template<comparable_key key_t_>
template<typename... key_args>
rb_node<key_t_>::rb_node(key_args &&... args)
    : key_(std::forward<key_args>(args)...) {
}

template<comparable_key key_t_>
inline void *rb_node<key_t_>::operator new(std::size_t size) {
  return resource_manager::allocate(size);
}

template<comparable_key key_t_>
inline void rb_node<key_t_>::operator delete(void *p) {
  resource_manager::deallocate(p, sizeof(rb_node<key_t_>));
}

template<comparable_key key_t_> inline rb_node<key_t_>::operator key_t_ &() {
  return key_;
}

template<comparable_key key_t_> inline std::uint8_t rb_node<key_t_>::color() const {
  return color_;
}

template<comparable_key key_t_> inline void rb_node<key_t_>::increase_color() {
  ++color_;
}

template<comparable_key key_t_>
inline void rb_node<key_t_>::pull_up_color() {
  auto left = atomic_left_.load(std::memory_order_relaxed);
  auto right = atomic_right_.load(std::memory_order_relaxed);
  if (left && left->color() > 0U
      && right && right->color() > 0U) {
    left->decrease_color();
    right->decrease_color();
  } else
    throw color_error("no node or color to pull up");
  ++color_;
}

template<comparable_key key_t_>
inline void rb_node<key_t_>::push_down_color() {
  if (color_ == 0)
    throw color_error("no color can be pushed down");

  auto left = atomic_left_.load(std::memory_order_relaxed);
  auto right = atomic_right_.load(std::memory_order_relaxed);
  if (left && right) {
    left->increase_color();
    right->increase_color();
  } else
    throw color_error("no node to push down color");
  --color_;
}

template<comparable_key key_t_>
inline typename rb_node<key_t_>::shared_node_t rb_node<key_t_>::get_child(side which) {
  auto &child = get_child_handle(which);
  return child.load(std::memory_order_relaxed);
}

template<comparable_key key_t_>
inline void rb_node<key_t_>::set_child(typename rb_node<key_t_>::shared_node_t child,
                                       side which) {
  auto &c = get_child_handle(which);
  c.store(child, std::memory_order_relaxed);
}

template<comparable_key key_t_>
inline typename rb_node<key_t_>::node_handle_t &rb_node<key_t_>::get_child_handle(side which) {
  return which == side::left ? atomic_left_ : atomic_right_;
}

template<comparable_key key_t_> inline void rb_node<key_t_>::decrease_color() {
  if (color_ > 0)
    --color_;
  else
    throw color_error("no color to decrease");
}

template<typename k_t_>
inline void rotate(std::atomic<std::shared_ptr<rb_node<k_t_>>> &parent, side which) {
/*
  1. rotate only when one of child is red
  2. parent child color also switch.
  3. prepare both new parent and child involving in rotating
  4. switch the root handle to new parent.
  */
  auto old_parent = parent.load(std::memory_order_relaxed);
  auto child = old_parent->get_child(which);
  if (!child || child->color() > 0)
    throw generic::rotate_error("child color must be red");

  auto new_child = std::make_shared<rb_node<k_t_>>((k_t_ &) *old_parent);
  auto new_parent = std::make_shared<rb_node<k_t_>>((k_t_ &) *child);

  if (old_parent->color() > 0)
    new_parent->increase_color();

  auto other_side = opposite(which);

  auto sibling = old_parent->get_child(other_side);
  new_child->set_child(sibling, other_side);
  auto other_grad_child = child->get_child(other_side);
  new_child->set_child(other_grad_child, which);

  auto which_grad_child = child->get_child(which);
  new_parent->set_child(which_grad_child, which);
  new_parent->set_child(new_child, other_side);

  parent.store(new_parent, std::memory_order_release);
}

} // namespace btree::node
