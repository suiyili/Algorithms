#pragma once

#include "consecutive_red_regulator.h"

using namespace btree::node;

namespace btree::algorithm {

template<comparable_key key_t_>
bool consecutive_red_regulator<key_t_>::regulate(rb_node<key_t_>::node_handle_t &handle, side which) {
  auto parent = handle.load(std::memory_order_acquire);
  if (parent->color() == 0) {
    if (reach_limit())
      throw std::runtime_error("more than 2 consecutive red nodes");
  } else {
    if (reach_limit()) {
      auto child_side = child_route_.top();
      child_route_.pop();
      auto grand_side = child_route_.top();
      child_route_.pop();
      auto sibling = parent->get_child(opposite(child_side));
      if (sibling && sibling->color() == 0)
        parent->push_down_color();
      else {
        if (child_side != grand_side)
          // rotate to make them same side.
          rotate(parent->get_child_handle(child_side), grand_side);
        rotate(handle, child_side);
      }
    } else {
      child_route_.pop();
      return false;
    }
  }
  child_route_.push(which);
  return true;
}

template<comparable_key key_t_>
inline bool consecutive_red_regulator<key_t_>::reach_limit() const {
  return child_route_.size() == 2U;
}

} // namespace btree::algorithm