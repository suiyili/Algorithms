#pragma once

#include "../dual_black_regulator/dual_black_regulator.hpp"
#include "../../generic/error_type.hpp"
#include "node_remover.h"
#include <queue>

namespace btree::algorithm {

template<comparable_key key_t_>
inline node_remover<key_t_>::node_remover(const key_t_ &key_to_remove)
    : to_remove_(key_to_remove) {}

template<comparable_key key_t_>
inline void node_remover<key_t_>::visit_raw(rb_node<key_t_> *&root) {
  /*
  1. stack the branch with removing node
  1.1 from top to the removing node.
  1.1 include extened items which needs min cut to extend the branch.

  2. if to be removed node has:
  2.1 no children, then make it color = 2 and remove it after graft.
  2.2 single child, replace it with the child value and sum the color.

  2. if any node has color > 1, then apply removal graft.
  */
  auto branch = find_removing_branch_raw(root);
  rb_node<key_t_> *&top = branch.top();
  auto removed = remove_raw(branch.top());
  // regulate color
  dual_black_regulator regulator(top, !removed);
  branch.pop();
  while (!branch.empty() && regulator.regulate(branch.top()))
    branch.pop();

  // make top black.
  if (root->color() == 0)
    root->increase_color();
  if (!removed)
    std::swap(removed, top);
  delete removed;
}

template<comparable_key key_t_>
typename rb_node<key_t_>::shared_rb_node_t node_remover<key_t_>::visit(typename rb_node<key_t_>::shared_rb_node_t root) {
  /*
  1. stack the branch with removing node
  1.1 from top to the removing node.
  1.1 include extened items which needs min cut to extend the branch.

  2. if to be removed node has:
  2.1 no children, then make it color = 2 and remove it after graft.
  2.2 single child, replace it with the child value and sum the color.

  2. if any node has color > 1, then apply removal graft.
  */

  auto branch = find_removing_branch(root);
  rb_node<key_t_> *&top = branch.top();
  auto removed = remove_raw(branch.top());
  // regulate color
  dual_black_regulator regulator(top, !removed);
  branch.pop();
  while (!branch.empty()
      && regulator.regulate(branch.top()))
    branch.pop();

  // make top black.
  if (root->color() == 0)
    root->increase_color();
  if (!removed)
    std::swap(removed, top);
  delete removed;
}

template<comparable_key key_t_>
inline branch_raw_t<key_t_>
node_remover<key_t_>::find_removing_branch_raw(rb_node<key_t_> *&root) {
  branch_raw_t<key_t_> branch_stack;

  branch_stack.emplace(root);

  while (branch_stack.top()) {
    auto &top = *branch_stack.top();
    auto &top_key = (const key_t_ &) top;
    if (to_remove_ < top_key)
      branch_stack.emplace(top.get_raw_child(side::left));
    else if (top_key < to_remove_)
      branch_stack.emplace(top.get_raw_child(side::right));
    else {
      append_right_min_raw(branch_stack);
      return std::move(branch_stack);
    }
  }
  throw item_not_exists("can not find node with given key");
}

template<comparable_key key_t_>
inline branch_t<key_t_> node_remover<key_t_>::find_removing_branch(typename rb_node<key_t_>::shared_rb_node_t root) {
  branch_t<key_t_> branch_stack;
  auto dummy_root = std::make_shared<rb_node<key_t_>>(to_remove_);
  dummy_root->set_child(root, root_side_);
  branch_stack.emplace(dummy_root, root_side_);
  auto top = root;

  while (top) {
    const key_t_ &top_key = *top;
    side child_side = to_remove_ < top_key
                      ? side::left : side::right;
    if (child_side == side::right && !(top_key < to_remove_)) {
      append_right_min(branch_stack);
      return std::move(branch_stack);
    } else {
      branch_stack.emplace(top, child_side);
      top = top->get_child(child_side);
    }
  }
  throw item_not_exists("can not find node with given key");
}

template<comparable_key key_t_>
inline void node_remover<key_t_>::append_right_min_raw(branch_raw_t<key_t_> &branch) {
  auto &to_remove = branch.top().get();
  if (both_children_available_raw(*to_remove)) {
    rb_node<key_t_> **next = &to_remove->get_raw_child(side::right);
    while (*next) {
      branch.emplace(*next);
      next = &(*next)->get_raw_child(side::left);
    }
    auto &k = (key_t_ &) *to_remove;
    k = (key_t_ &) *branch.top();
  }
}
template<comparable_key key_t_>
inline void node_remover<key_t_>::append_right_min(branch_t<key_t_> &branch) {
  auto &[top_node, top_side] = branch.top();
  auto to_remove = top_node->get_child(top_side);
  if (both_children_available(to_remove)) {
    std::queue<typename rb_node<key_t_>::shared_rb_node_t> left_branch;
    auto next = to_remove->get_child(side::right);
    while (next)  {
      left_branch.push(next);
      next = next->get_child(side::left);
    }

    auto &k = (key_t_ &) *left_branch.back();
    auto to_replace = std::make_shared<rb_node<key_t_>>(k);
    to_replace->set_child(to_remove->get_child(side::left), side::left);
    to_replace->set_child(to_remove->get_child(side::right), side::right);
    top_node->set_child(to_replace, top_side);

    branch.emplace(to_replace, side::right);
    for(auto& n : left_branch)
      branch.emplace(n, side::left);
  }
}
template<comparable_key key_t_>
inline rb_node<key_t_> *node_remover<key_t_>::remove_raw(rb_node<key_t_> *&to_remove) {
  rb_node<key_t_> *rid = nullptr;
  auto right_child = get_single_child(*to_remove);
  if (right_child) {
    if (to_remove->color() > 0)
      to_remove->push_down_color_raw();
    rid = to_remove;
    to_remove = right_child;
  }
  return rid;
}
template<comparable_key key_t_>
inline bool node_remover<key_t_>::both_children_available_raw(rb_node<key_t_> &parent) {
  return parent.get_raw_child(side::left) && parent.get_raw_child(side::right);
}
template<comparable_key key_t_>
inline bool node_remover<key_t_>::both_children_available(typename rb_node<key_t_>::shared_rb_node_t parent) {
  return parent.get_child(side::left) && parent.get_child(side::right);
}
template<comparable_key key_t_>
rb_node<key_t_> *node_remover<key_t_>::get_single_child(rb_node<key_t_> &parent) {
  auto left_child = parent.get_raw_child(side::left);
  return left_child ? left_child : parent.get_raw_child(side::right);
}

} // namespace btree::algorithm