#pragma once

#include <generic/error_type.hpp>
#include "remove_node.h"

namespace btree::algo {

template<comparable_key key_t_>
static bool both_children_available(const typename rb_node<key_t_>::shared_node_t &parent);

template<comparable_key key_t_>
static void append_right_min(branch_stack_t<key_t_> &branch);

template<comparable_key key_t_>
inline scope_node_remover<key_t_> remove_node(typename rb_node<key_t_>::node_handle_t &root, const key_t_ &to_remove) {
  /*
   1. stack the branch with removing node
   1.1 from top to the removing node.
   1.1 include extended items which needs min cut to extend the branch.
   */

  branch_stack_t<key_t_> stack_branch;
  stack_branch.emplace(root, side::left); //dummy side for root.
  auto top = root.load(std::memory_order_acquire);

  while (top) {
    auto &top_key = (const key_t_ &) *top;
    side child_side = to_remove < top_key
                      ? side::left : side::right;
    if (child_side == side::right && !(top_key < to_remove)) {
      append_right_min<key_t_>(stack_branch);
      return scope_node_remover<key_t_>(stack_branch);
    } else {
      stack_branch.emplace(top->get_child_handle(child_side), child_side);
      top = top->get_child(child_side);
    }
  }
  throw item_not_exists("can not find node with given key");
}

template<comparable_key key_t_>
inline void append_right_min(branch_stack_t<key_t_> &branch) {

  auto [top, top_side] = branch.top();
  auto &top_handle = top.get();
  auto to_remove = top_handle.load(std::memory_order_acquire);
  if (both_children_available<key_t_>(to_remove)) {
    auto next = to_remove->get_child(side::right);
    while (auto child = next->get_child(side::left))
      next = child;

    //make copy of the nearest right node
    //switch the copy with the pending removing one.
    //keep the nearest right as x to remove in next step.
    auto &k = (key_t_ &) *next;
    auto to_replace = std::make_shared<rb_node<key_t_>>(k);
    to_replace->set_child(to_remove->get_child(side::left), side::left);
    to_replace->set_child(to_remove->get_child(side::right), side::right);
    if (to_remove->color())
      to_replace->increase_color();
    top_handle.store(to_replace, std::memory_order_release);
    branch.emplace(to_replace->get_child_handle(side::right), side::right);
    next = to_replace->get_child(side::right);
    while (auto child = next->get_child(side::left)) {
      branch.emplace(next->get_child_handle(side::left), side::left);
      next = child;
    }
  }
}

template<comparable_key key_t_>
inline bool both_children_available(const typename rb_node<key_t_>::shared_node_t &parent) {
  return parent->get_child(side::left)
      && parent->get_child(side::right);
}

template<comparable_key key_t_>
inline scope_node_remover<key_t_>::scope_node_remover(branch_stack_t<key_t_> branch)
    : branch_(std::move(branch)){
/*
  2. if to be removed node has:
  2.1 no children, then make it color = 2 and remove it after graft.
  2.2 single child, replace it with the child value and keep it black.
      since child never will have same color as its parent black child.

  2. if any node has color > 1, then apply removal graft.
  */
  if(branch_.empty()) return;

  auto [node_to_remove, _] = branch_.top();
  to_remove_ = &node_to_remove.get();
  auto to_remove = to_remove_->load(std::memory_order_acquire);
  auto left_child = to_remove->get_child(side::left);
  auto child = left_child ? left_child : to_remove->get_child(side::right);
  if (child) {
    if (to_remove->color() > 0)
      child->increase_color();
    to_remove_->store(child, std::memory_order_release);
    to_remove_ = nullptr;
  } else
    to_remove->increase_color();
}

template<comparable_key key_t_>
scope_node_remover<key_t_>::~scope_node_remover() {
  if(to_remove_)
    to_remove_->store(nullptr, std::memory_order_release);
}

template<comparable_key key_t_>
branch_stack_t<key_t_> &scope_node_remover<key_t_>::get_branch() {
  return branch_;
}

} // namespace btree::algo