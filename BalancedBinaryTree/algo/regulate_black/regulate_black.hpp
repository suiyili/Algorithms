#pragma once

#include "regulate_black.h"

namespace btree::algo {

template<comparable_key key_t_>
bool is_black(const typename rb_node<key_t_>::shared_node_t& node);

template<comparable_key key_t_>
void rotate_sibling(typename rb_node<key_t_>::node_handle_t &parent_handle, side which);

template<comparable_key key_t_>
void regulate_black(branch_stack_t<key_t_> &branch) {
  if(branch.empty()) return;

  auto &[top_ref, x_side] = branch.top();
  auto& top_handle = top_ref.get();
  auto parent = top_handle.load(std::memory_order_acquire);
  branch.pop();//pop the first one which represent x, we start from its parent.
  while (!branch.empty()) {
    auto &[parent_ref, parent_side] = branch.top();
    auto& parent_handle = parent_ref.get();
    parent = parent_handle.load(std::memory_order_acquire);
    auto x_child = parent->get_child(x_side);

    if (x_child->color() < 2)
      break;
    branch_stack_t<key_t_> parents;
    parents.emplace(parent_handle, parent_side);

    auto sibling_side = opposite(x_side);
    auto sibling = parent->get_child(sibling_side);
    // case 1, x has red sibling
    if (sibling && !sibling->color()) {
      //rotate the sibling to have x-side nephew as new sibling.
      rotate(parent_handle, sibling_side);
      //the new parent is the prev sibling, but anchor on exiting parent_handle.
      parent = parent_handle.load(std::memory_order_relaxed);
      //the now x-side child of new parent is prev parent.
      //add its handle on top of the branch.
      branch.emplace(parent->get_child_handle(x_side), x_side);
    } else {
      rotate_sibling<key_t_>(parent_handle, x_side);
      //parent becomes child, one step back.
      x_side = parent_side;
      branch.pop();
    }
  }
  if(parent->color() > 1)
    parent->decrease_color();
}

template<comparable_key key_t_>
void rotate_sibling(typename rb_node<key_t_>::node_handle_t &parent_handle, side which) {
  // suppose sibling is black.
  auto parent = parent_handle.load(std::memory_order_acquire);
  auto sibling_side = opposite(which);
  auto sibling = parent->get_child(sibling_side);

  auto x_side_black = is_black<key_t_>(sibling->get_child(which));
  auto w_side_black = is_black<key_t_>(sibling->get_child(sibling_side));

  auto upgrade = x_side_black && w_side_black;
  if (!upgrade) {
    // w side is black, so x_side is red,
    // now make w side nephew red.
    if (w_side_black)
      rotate(parent->get_child_handle(sibling_side), which);
    //sibling has been replaced, need update
    sibling = parent->get_child(sibling_side);
    sibling->push_down_color();
    rotate(parent_handle, sibling_side);
    //parent rotated, get old parent.
    sibling = parent_handle.load(std::memory_order_relaxed);
    parent = sibling->get_child(which);
  }
  parent->pull_up_color();
}

template<comparable_key key_t_>
bool is_black(const typename rb_node<key_t_>::shared_node_t& node) {
  return !node || node->color();
}

} // namespace btree::algo