#pragma once

#include <generic/error_type.hpp>
#include "insert_node.h"

namespace btree::algo {

template<comparable_key key_t_>
typename rb_node<key_t_>::shared_node_t get_top(
    branch_stack_t<key_t_> &stack_branch);

template<comparable_key key_t_>
inline branch_stack_t<key_t_> insert_node(typename rb_node<key_t_>::node_handle_t& root,
                                          std::unique_ptr<rb_node<key_t_>> to_insert) {
  auto & key_to_insert = (key_t_&)*to_insert;
  branch_stack_t<key_t_> stack_branch;
  stack_branch.emplace(root, side::left);
  while (auto child = get_top<key_t_>(stack_branch)) {
    auto &child_key = (key_t_ &) *child;
    auto child_side = key_to_insert < child_key ? side::left
                                            : child_key < key_to_insert ? side::right
                                                                    : throw item_already_exists("node already exists");
    stack_branch.emplace(child->get_child_handle(child_side), child_side);
  }
  typename rb_node<key_t_>::node_handle_t &node = stack_branch.top().first;
  node.store(std::move(to_insert), std::memory_order_relaxed);
  return stack_branch;
}

template<comparable_key key_t_>
inline typename rb_node<key_t_>::shared_node_t get_top(
    branch_stack_t<key_t_> &stack_branch) {
  typename rb_node<key_t_>::node_handle_t &node = stack_branch.top().first;
  return node.load(std::memory_order_relaxed);
}

} // namespace btree::algo