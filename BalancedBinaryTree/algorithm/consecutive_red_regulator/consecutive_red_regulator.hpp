#pragma once

#include "consecutive_red_regulator.h"

using namespace btree::node;

namespace btree::algorithm {

template<comparable_key key_t_>
inline consecutive_red_regulator<key_t_>::consecutive_red_regulator()
    : chain_old_{nullptr, nullptr}, count_(0U) {
    }

template<comparable_key key_t_>
inline bool consecutive_red_regulator<key_t_>::regulate_raw(rb_node<key_t_> *&item) {
  if (item->color() == 0) {
    if (count_ == sizeof(chain_old_))
      throw std::runtime_error("more than 2 consecutive red nodes");
    chain_old_[count_++] = &item;
  } else {
    auto two_red = count_ == 2;
    count_ = 0U;
    if (two_red) {
      auto red_child_side = get_child_side_raw(item, *chain_old_[1]);
      auto sibling = item->get_raw_child(opposite(red_child_side));
      if (sibling && sibling->color() == 0)
        item->push_down_color_raw();
      else {
        auto red_grand_side = get_child_side_raw(*chain_old_[1], *chain_old_[0]);
        if (red_child_side != red_grand_side)
          // rotate to make them same side.
          rotate_raw(*chain_old_[1], red_grand_side);

        rotate_raw(item, red_child_side);
      }
      chain_old_[count_++] = &item;
    } else
      return false;
  }
  return true;
}

template<comparable_key key_t_>
inline bool consecutive_red_regulator<key_t_>::regulate(
    typename rb_node<key_t_>::shared_rb_node_t root, side parent_side) {
  auto parent = root->get_child(parent_side);
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
          parent->rotate(child_side, grand_side);
        root->rotate(parent_side, child_side);
      }
    } else {
      child_route_.pop();
      return false;
    }
  }
  child_route_.push(parent_side);
  return true;
}

template<comparable_key key_t_>
inline side
consecutive_red_regulator<key_t_>::get_child_side_raw(rb_node<key_t_> *parent,
                                                      rb_node<key_t_> *child) {
  return parent->get_raw_child(side::left) == child ? side::left : side::right;
}
template<comparable_key key_t_>
inline bool consecutive_red_regulator<key_t_>::reach_limit() const {
  return child_route_.size() == 2U;
}

} // namespace btree::algorithm