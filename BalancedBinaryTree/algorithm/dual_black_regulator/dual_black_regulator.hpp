#pragma once

#include "dual_black_regulator.h"

namespace btree::algorithm {

template<comparable_key key_t_>
inline dual_black_regulator<key_t_>::dual_black_regulator(side x_side)
    : x_side_(x_side) {
}

template<comparable_key key_t_>
bool dual_black_regulator<key_t_>::regulate(typename rb_node<key_t_>::node_handle_t &root, side which) {
  auto parent = root.load(std::memory_order_acquire);
  auto dual_black = parent->get_child(x_side_);

  if (dual_black->color() < 2)
    return false;

  branch_stack_t<key_t_> parents;
  parents.emplace(root, which);

  auto sibling_side = opposite(x_side_);
  auto sibling = parent->get_child(sibling_side);
  // case 1
  if (sibling && !sibling->color()) {
    rotate(root, sibling_side);
    parent = root.load(std::memory_order_relaxed);
    parents.emplace(parent->get_child_handle(x_side_), x_side_);
  }
  // case 2,3,4
  while (!parents.empty()) {
    auto [n, s] = parents.top();
    if (rotate_sibling(n, s))
      parents.pop();
    else
      break;
  }

  x_side_ = which;
  return true;
}

template<comparable_key key_t_>
bool dual_black_regulator<key_t_>::rotate_sibling(typename rb_node<key_t_>::node_handle_t &root, side which) {
  // suppose sibling is black.
  auto parent = root.load(std::memory_order_acquire);
  auto sibling_side = opposite(x_side_);
  auto sibling = parent->get_child(sibling_side);

  auto x_side_black = is_black(sibling->get_child(x_side_));
  auto w_side_black = is_black(sibling->get_child(sibling_side));

  auto upgrade = x_side_black && w_side_black;
  if (!upgrade) {
    // w side is black, so x_side is red,
    // now make w side nephew red.
    if (w_side_black)
      rotate(parent->get_child_handle(sibling_side), x_side_);
    //sibling has been replaced, need update
    sibling = parent->get_child(sibling_side);
    sibling->push_down_color();
    rotate(root, sibling_side);
    //parent rotated, get old parent.
    sibling = root.load(std::memory_order_relaxed);
    parent = sibling->get_child(x_side_);
  }

  parent->pull_up_color();
  return parent->color() > 1;
}

template<comparable_key key_t_>
bool dual_black_regulator<key_t_>::is_black(const typename rb_node<key_t_>::shared_node_t& node) {
  return !node || node->color();
}

} // namespace btree::algorithm