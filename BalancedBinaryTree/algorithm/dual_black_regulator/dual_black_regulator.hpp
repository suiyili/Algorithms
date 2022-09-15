#pragma once

#include "dual_black_regulator.h"

namespace btree::algorithm {

template<comparable_key key_t_>
inline btree::algorithm::dual_black_regulator<key_t_>::dual_black_regulator(
    rb_node<key_t_> *dual_black_item, bool force)
    : dual_black_item_(dual_black_item), x_side_(side::left), force_(force) {
  if (force && dual_black_item_->color() == 1)
    dual_black_item_->increase_color();
}

template<comparable_key key_t_>
inline dual_black_regulator<key_t_>::dual_black_regulator(side x_side, bool force)
    : x_side_(x_side), force_(force) {
}

template<comparable_key key_t_>
inline bool dual_black_regulator<key_t_>::regulate(rb_node<key_t_> *&parent) {
  if (dual_black_item_->color() < 2)
    return false;

  branch_raw_t<key_t_> parents;
  parents.emplace(parent);

  auto x_side = get_side(parent, dual_black_item_);
  auto sibling_side = opposite(x_side);
  auto sibling = parent->get_raw_child(sibling_side);
  // case 1
  if (sibling && !sibling->color()) {
    rotate_raw(parent, sibling_side);
    parents.emplace(parent->get_raw_child(x_side));
  }
  // case 2,3,4
  while (!parents.empty()
      && rotate_sibling_raw(parents.top(), x_side))
    parents.pop();

  dual_black_item_ = parent;
  return true;
}

template<comparable_key key_t_>
bool dual_black_regulator<key_t_>::regulate(typename rb_node<key_t_>::shared_rb_node_t root, side parent_side) {
  auto parent = root->get_child(parent_side);
  auto dual_black = parent->get_child(x_side_);
  if (force_ && dual_black->color() == 1) {
    dual_black->increase_color();
    force_ = false;
  }
  if (dual_black->color() < 2)
    return false;

  branch_t<key_t_> parents;
  parents.emplace(root, parent_side);

  auto sibling_side = opposite(x_side_);
  auto sibling = parent->get_child(sibling_side);
  // case 1
  if (sibling && !sibling->color()) {
    root->rotate(parent_side, sibling_side);
    parents.emplace(root->get_child(parent_side), x_side_);
  }
  // case 2,3,4
  while (!parents.empty()) {
    auto [n, s] = parents.top();
    if (rotate_sibling(n, s))
      parents.pop();
    else
      break;
  }

  x_side_ = parent_side;
  return true;

}

template<comparable_key key_t_>
inline side dual_black_regulator<key_t_>::get_side(rb_node<key_t_> *parent,
                                                   rb_node<key_t_> *child) {
  auto left_child = parent->get_raw_child(side::left);
  return left_child == child ? side::left : side::right;
}
template<comparable_key key_t_>
inline bool dual_black_regulator<key_t_>::rotate_sibling_raw(rb_node<key_t_> *&parent,
                                                             side x_side) {
  // suppose sibling is black.
  auto sibling_side = opposite(x_side);
  auto &sibling = parent->get_raw_child(sibling_side);

  auto x_side_black = is_black_raw(sibling->get_raw_child(x_side));
  auto w_side_black = is_black_raw(sibling->get_raw_child(sibling_side));

  auto upgrade = x_side_black && w_side_black;
  auto old_parent = parent;
  if (!upgrade) {
    // w side is black, so x_side is red,
    // now make w side nephew red.
    if (w_side_black)
      rotate_raw(sibling, x_side);
    sibling->push_down_color_raw();
    rotate_raw(parent, sibling_side);
  }
  old_parent->pull_up_color_raw();
  return old_parent->color() > 1;
}
template<comparable_key key_t_>
inline bool dual_black_regulator<key_t_>::rotate_sibling(typename rb_node<key_t_>::shared_rb_node_t root,
                                                         side parent_side) {
  // suppose sibling is black.
  auto parent = root->get_child(parent_side);
  auto sibling_side = opposite(x_side_);
  auto sibling = parent->get_child(sibling_side);

  auto x_side_black = is_black(sibling->get_child(x_side_));
  auto w_side_black = is_black(sibling->get_child(sibling_side));

  auto upgrade = x_side_black && w_side_black;
  if (!upgrade) {
    // w side is black, so x_side is red,
    // now make w side nephew red.
    if (w_side_black)
      parent->rotate(sibling_side, x_side_);
    //sibling has been replaced, need update
    sibling = parent->get_child(sibling_side);
    sibling->push_down_color();
    root->rotate(parent_side, sibling_side);
    //parent rotated, need update
    sibling = root->get_child(parent_side);
    parent = sibling->get_child(x_side_);
  }

  parent->pull_up_color();
  return parent->color() > 1;
}

template<comparable_key key_t_>
inline bool dual_black_regulator<key_t_>::is_black_raw(rb_node<key_t_> *item) {
  return !item || item->color();
}
template<comparable_key key_t_>
bool dual_black_regulator<key_t_>::is_black(typename rb_node<key_t_>::shared_rb_node_t node) {
  return !node || node->color();
}

} // namespace btree::algorithm