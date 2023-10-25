#pragma once

#include <algorithm/consecutive_red_regulator/consecutive_red_regulator.hpp>
#include <generic/error_type.hpp>
#include "node_inserter.h"

namespace btree::algorithm {

template<comparable_key key_t_>
template<typename... key_args>
inline node_inserter<key_t_>::node_inserter(key_args &&... args)
    : to_insert_(std::forward<key_args>(args)...) {
}

template<comparable_key key_t_>
inline node_inserter<key_t_>::node_inserter(node_inserter<key_t_> &&other) noexcept
    : to_insert_(std::move(other.to_insert_)) {}

template<comparable_key key_t_>
inline void node_inserter<key_t_>::visit(typename rb_node<key_t_>::node_handle_t &root) {

  auto branch = get_insert_branch(root);
  regulate_red(branch);
  auto root_ptr = root.load(std::memory_order_relaxed);
  if (root_ptr->color() == 0)
    root_ptr->increase_color();
}

template<comparable_key key_t_>
branch_stack_t<key_t_> node_inserter<key_t_>::get_insert_branch(
    typename rb_node<key_t_>::node_handle_t &root) {
  branch_stack_t<key_t_> stack_branch;
  stack_branch.emplace(root, root_side_);
  while (auto child = get_top(stack_branch)) {
    auto &child_key = (const key_t_ &) *child;
    auto child_side = to_insert_ < child_key ? side::left
                                             : child_key < to_insert_ ? side::right
                                                                      : throw item_already_exists("node already exists");
    stack_branch.emplace(child->get_child_handle(child_side), child_side);
  }
  typename rb_node<key_t_>::node_handle_t &node = stack_branch.top().first;
  node.store(std::make_shared<rb_node<key_t_>>(to_insert_), std::memory_order_relaxed);
  return stack_branch;
}

template<comparable_key key_t_>
typename rb_node<key_t_>::shared_node_t node_inserter<key_t_>::get_top(
    branch_stack_t<key_t_> &stack_branch) {
  typename rb_node<key_t_>::node_handle_t &node = stack_branch.top().first;
  return node.load(std::memory_order_relaxed);
}

template<comparable_key key_t_>
inline void node_inserter<key_t_>::regulate_red(branch_stack_t<key_t_> &branch) {
  consecutive_red_regulator<key_t_> regulator;
  while (!branch.empty()) {
    auto &[node, which] = branch.top();
    if (regulator.regulate(node, which))
      branch.pop();
    else
      break;
  }
}

} // namespace btree::algorithm