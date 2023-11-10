#pragma once

#include "regulate_red.h"

namespace btree::algo {

bool updateRoute(std::stack<side>& route, side which, bool color);

template<comparable_key key_t_>
inline void regulate_red(branch_stack_t<key_t_> &branch) {
  typename rb_node<key_t_>::shared_node_t root;
  std::stack<side> child_route;
  while (!branch.empty()) {
    auto &[node, which] = branch.top();
    branch.pop();
    auto &handle = node.get();
    auto parent = handle.load(std::memory_order_acquire);
    if (!updateRoute(child_route, which, parent->color())){
      auto child_side = child_route.top();
      child_route.pop();
      auto grand_side = child_route.top();
      child_route.pop();
      auto sibling = parent->get_child(opposite(child_side));
      if (sibling && sibling->color() == 0)
        parent->push_down_color();
      else {
        if (child_side != grand_side)
          // rotate to make them same side.
          rotate(parent->get_child_handle(child_side), grand_side);
        rotate(handle, child_side);
      }
    }
    root = handle.load(std::memory_order_acquire);
  }
  if (root && root->color() == 0)
    root->increase_color();
}

inline bool updateRoute(std::stack<side>& route, side which, bool color) {
  if (route.size() == 2) {
    if (color)
      return false;
    throw std::runtime_error("more than 2 consecutive red nodes");
  } else {
    //route only contains red(0 color) node side.
    //if there is no consecutive red parent-child node.
    //then, continue loop(return true)
    if (color) {
      if (!route.empty())
        route.pop();
    } else
      route.push(which);
  }
  return true;
}

} // namespace btree::algo