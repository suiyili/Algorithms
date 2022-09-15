#pragma once

#include "../consecutive_red_regulator/consecutive_red_regulator.hpp"
#include "../../generic/error_type.hpp"
#include "node_inserter.h"

namespace btree::algorithm {

template<comparable_key key_t_>
template<typename... key_args>
inline node_inserter<key_t_>::node_inserter(key_args &&... args)
    : to_insert_raw_(new rb_node<key_t_>(std::forward<key_args>(args)...)),
      to_insert_(std::make_shared<rb_node<key_t_>>(std::forward<key_args>(args)...)) {
}

template<comparable_key key_t_>
node_inserter<key_t_>::~node_inserter() {
  delete to_insert_raw_;
}

template<comparable_key key_t_>
inline node_inserter<key_t_>::node_inserter(node_inserter<key_t_> &&other) noexcept
    : to_insert_raw_(other.to_insert_raw_), to_insert_(std::move(other.to_insert_)) {}

template<comparable_key key_t_>
inline typename ::rb_node<key_t_>::shared_rb_node_t
node_inserter<key_t_>::visit(typename rb_node<key_t_>::shared_rb_node_t root) {
  auto dummy_root = std::make_shared<rb_node<key_t_>>((key_t_) *to_insert_);
  dummy_root->set_child(root, root_side_);
  auto branch = get_insert_branch(dummy_root);
  regulate_red(std::move(branch));
  auto new_root = dummy_root->get_child(root_side_);
  if (new_root->color() == 0)
    new_root->increase_color();
  return new_root;
}

template<comparable_key key_t_>
inline void node_inserter<key_t_>::visit_raw(rb_node<key_t_> *&root) {
  auto branch = insert_to_branch_raw(root);
  regulate_red_color(std::move(branch));
  if (root->color() == 0)
    root->increase_color();
}

template<comparable_key key_t_>
inline branch_raw_t<key_t_> node_inserter<key_t_>::insert_to_branch_raw(rb_node<key_t_> *&root) {
  branch_raw_t<key_t_> branch_stack;

  auto &key = (const key_t_ &) *to_insert_raw_;
  branch_stack.push(root);

  while (branch_stack.top()) {
    auto &top = *branch_stack.top();
    auto &top_key = (const key_t_ &) top;
    if (key < top_key)
      branch_stack.emplace(top.get_raw_child(side::left));
    else if (top_key < key)
      branch_stack.emplace(top.get_raw_child(side::right));
    else
      throw item_already_exists("node already exists");
  }

  branch_stack.top().get() = to_insert_raw_;
  to_insert_raw_ = nullptr;

  return std::move(branch_stack);
}

template<comparable_key key_t_>
inline branch_t<key_t_> node_inserter<key_t_>::get_insert_branch(typename rb_node<key_t_>::shared_rb_node_t root) {

  auto &key = (const key_t_ &) *to_insert_;
  branch_t<key_t_> branch_stack;

  auto parent = root;
  auto child_side = root_side_;
  while (true) {
    branch_stack.emplace(parent, child_side);
    auto child = parent->get_child(child_side);
    if (child) {
      parent = child;
      auto &child_key = (const key_t_ &) *parent;
      child_side = key < child_key ? side::left
                                   : child_key < key ? side::right
                                                     : throw item_already_exists("node already exists");
    } else {
      parent->set_child(std::move(to_insert_), child_side);
      break;
    }
  }
  return std::move(branch_stack);
}
template<comparable_key key_t_>
inline void node_inserter<key_t_>::regulate_red_color(branch_raw_t<key_t_> branch) {
  consecutive_red_regulator<key_t_> regulator;
  while (!branch.empty() && regulator.regulate_raw(branch.top()))
    branch.pop();
}
template<comparable_key key_t_>
inline void node_inserter<key_t_>::regulate_red(branch_t<key_t_> branch) {
  consecutive_red_regulator<key_t_> regulator;
  while (!branch.empty()) {
    auto [node, which] = branch.top();
    if (regulator.regulate(node, which))
      branch.pop();
    else
      break;
  }
}

} // namespace btree::algorithm