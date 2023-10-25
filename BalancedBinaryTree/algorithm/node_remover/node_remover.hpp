#pragma once

#include <algorithm/dual_black_regulator/dual_black_regulator.hpp>
#include <generic/error_type.hpp>
#include "node_remover.h"
#include <queue>

namespace btree::algorithm {

template<comparable_key key_t_>
template<typename... key_args>
inline node_remover<key_t_>::node_remover(key_args &&... args)
    : to_remove_(std::forward<key_args>(args)...) {
}

template<comparable_key key_t_>
inline void node_remover<key_t_>::visit(typename rb_node<key_t_>::node_handle_t &root) {
  /*
   1. stack the branch with removing node
   1.1 from top to the removing node.
   1.1 include extended items which needs min cut to extend the branch.

   2. if to be removed node has:
   2.1 no children, then make it color = 2 and remove it after graft.
   2.2 single child, replace it with the child value and sum the color.

   2. if any node has color > 1, then apply removal graft.
   */

  auto branch = make_removing_branch(root);
  auto [to_remove, which_to_remove] = branch.top();
  auto &node_to_remove = to_remove.get();
  auto is_removed = remove(node_to_remove);
  // regulate color
  dual_black_regulator<key_t_> regulator(which_to_remove);
  branch.pop();//pop the first one which is father, we need grandpa.
  while (!branch.empty()) {
    auto &[dual_parent, dual_state] = branch.top();
    if (!regulator.regulate(dual_parent.get(), dual_state))
      break;
    branch.pop();
  }

  // make top black.
  auto n = root.load(std::memory_order_acquire);
  if (n->color() == 0)
    n->increase_color();
  //if removed color > 0, means it is removed from tree when calling remove.
  //otherwise, it is still in the tree, we have to cut it out.
  if (!is_removed)
    node_to_remove.store(nullptr, std::memory_order_release);
}

template<comparable_key key_t_>
branch_stack_t<key_t_> node_remover<key_t_>::make_removing_branch(
    rb_node<key_t_>::node_handle_t &root) {
  branch_stack_t<key_t_> stack_branch;
  stack_branch.emplace(root, root_side_);
  auto top = root.load(std::memory_order_acquire);

  while (top) {
    auto &top_key = (const key_t_ &) *top;
    side child_side = to_remove_ < top_key
                      ? side::left : side::right;
    if (child_side == side::right && !(top_key < to_remove_)) {
      append_right_min(stack_branch);
      return std::move(stack_branch);
    } else {
      stack_branch.emplace(top->get_child_handle(child_side), child_side);
      top = top->get_child(child_side);
    }
  }
  throw item_not_exists("can not find node with given key");
}

template<comparable_key key_t_>
void node_remover<key_t_>::append_right_min(branch_stack_t<key_t_> &branch) {

  auto [top, top_side] = branch.top();
  auto &top_node = top.get();
  auto to_remove = top_node.load(std::memory_order_acquire);
  if (both_children_available(to_remove)) {
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
    top_node.store(to_replace, std::memory_order_release);
    branch.emplace(to_replace->get_child_handle(side::right), side::right);
    next = to_replace->get_child(side::right);
    while (auto child = next->get_child(side::left)) {
      branch.emplace(next->get_child_handle(side::left), side::left);
      next = child;
    }
  }
}

template<comparable_key key_t_>
bool node_remover<key_t_>::remove(rb_node<key_t_>::node_handle_t &handle) {
  auto to_remove = handle.load(std::memory_order_acquire);
  auto left_child = to_remove->get_child(side::left);
  auto child = left_child ? left_child : to_remove->get_child(side::right);
  if (child) {
    if (to_remove->color() > 0)
      child->increase_color();
    handle.store(child, std::memory_order_release);
  } else
    to_remove->increase_color();
  return (bool) child;
}

template<comparable_key key_t_>
inline bool node_remover<key_t_>::both_children_available(
    const typename rb_node<key_t_>::shared_node_t &parent) {
  return parent->get_child(side::left)
      && parent->get_child(side::right);
}

} // namespace btree::algorithm