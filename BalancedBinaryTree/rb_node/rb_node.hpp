#pragma once

#include "../generic/error_type.hpp"
#include "rb_node.h"
#include "../generic/resource_manager/resource_manager.hpp"

namespace btree::node {

inline side opposite(side which) {
  return which == side::left ? side::right : side::left;
}

template<comparable_key key_t_>
template<typename... _key_args>
rb_node<key_t_>::rb_node(_key_args &&... args)
    : key_(std::forward<_key_args>(args)...) {
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

template<comparable_key key_t_> inline void rb_node<key_t_>::pull_up_color_raw() {

  pull_up_color_raw(left_);
  pull_up_color_raw(right_);

  ++color_;
}

template<comparable_key key_t_> inline void rb_node<key_t_>::push_down_color_raw() {
  if (color_ == 0)
    throw color_error("no color can be pushed down");

  push_down_color_raw(left_);
  push_down_color_raw(right_);
  --color_;
}

template<comparable_key key_t_>
inline void rb_node<key_t_>::pull_up_color() {
  pull_up_color(atomic_left_.load(std::memory_order_relaxed));
  pull_up_color(atomic_right_.load(std::memory_order_relaxed));

  ++color_;
}

template<comparable_key key_t_>
inline void rb_node<key_t_>::push_down_color() {
  if (color_ == 0)
    throw color_error("no color can be pushed down");

  push_down_color(atomic_left_.load(std::memory_order_relaxed));
  push_down_color(atomic_right_.load(std::memory_order_relaxed));
  --color_;
}

template<comparable_key key_t_>
inline rb_node<key_t_> *&rb_node<key_t_>::get_raw_child(side which) {
  return which == side::left ? left_ : right_;
}

template<comparable_key key_t_>
inline typename rb_node<key_t_>::shared_rb_node_t rb_node<key_t_>::get_child(side which) {
  auto &child = get_child_ref(which);
  return child.load(std::memory_order_relaxed);
}

template<comparable_key key_t_>
inline void rb_node<key_t_>::set_child(typename rb_node<key_t_>::shared_rb_node_t child,
                                                                      side which) {
  auto &c = get_child_ref(which);
  c.store(child, std::memory_order_relaxed);
}

template<comparable_key key_t_>
inline void rb_node<key_t_>::rotate(side parent_side, side child_side) {
  auto& root = get_child_ref(parent_side);
  auto parent = root.load(std::memory_order_relaxed);
  auto child = parent->get_child(child_side);
  if (!child || child->color() > 0)
    throw generic::rotate_error("child color must be red");

  auto new_child = std::make_shared<rb_node<key_t_>>((key_t_ &) *parent);
  auto new_parent = std::make_shared<rb_node<key_t_>>((key_t_ &) *child);

  if (parent->decrease_color())
    new_parent->increase_color();

  auto other_side = opposite(child_side);

  auto sibling = parent->get_child(other_side);
  new_child->set_child(sibling, other_side);
  auto other_grad_child = child->get_child(other_side);
  new_child->set_child(other_grad_child, child_side);

  auto which_grad_child = child->get_child(child_side);
  new_parent->set_child(which_grad_child, child_side);
  new_parent->set_child(new_child, other_side);

  root.store(new_parent, std::memory_order_release);
}

template<comparable_key key_t_>
inline typename rb_node<key_t_>::atomic_shared_rb_node_t &rb_node<key_t_>::get_child_ref(side which) {
  return which == side::left ? atomic_left_ : atomic_right_;
}

template<comparable_key key_t_> inline bool rb_node<key_t_>::decrease_color() {
  bool to_reduce = color_ > 0;
  if (to_reduce)
    --color_;
  return to_reduce;
}

template<comparable_key key_t_>
inline void rb_node<key_t_>::push_down_color_raw(rb_node *child) {
  if (child)
    child->increase_color();
}
template<comparable_key key_t_>
inline void rb_node<key_t_>::pull_up_color_raw(rb_node *child) {
  if (child && !child->decrease_color())
    throw color_error("no color can be pulled up");
}
template<comparable_key key_t_>
void rb_node<key_t_>::pull_up_color(rb_node<key_t_>::shared_rb_node_t child) {
  if (child && !child->decrease_color())
    throw color_error("no color can be pulled up");
}
template<comparable_key key_t_>
void rb_node<key_t_>::push_down_color(rb_node<key_t_>::shared_rb_node_t child) {
  if (child)
    child->increase_color();
}

template<comparable_key key_t_> inline void rotate_raw(rb_node<key_t_> *&item, side which) {
  /*
 1. rotate only when one of child is red
 2. parent child color also switch.
 */

  auto &child = item->get_raw_child(which);
  if (!child || child->color() > 0)
    throw generic::rotate_error("child color must be red");

  if (item->decrease_color())
    child->increase_color();

  auto &grand_child = child->get_raw_child(opposite(which));
  auto temp = child;
  child = grand_child;
  grand_child = item;
  item = temp;
}
} // namespace btree::node
