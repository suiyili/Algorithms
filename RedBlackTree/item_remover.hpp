#pragma once

#include "item_remover.h"
#include "item_not_exists.hpp"
#include "graft_for_removing.hpp"

namespace bbtree::algorithm {

template <ComparableKey Key>
inline item_remover<Key>::item_remover(const Key &key_to_remove)
    : to_remove_(key_to_remove), removed_(nullptr) {}

template <ComparableKey Key> 
inline item_remover<Key>::~item_remover() {
  delete removed_;
}

template <ComparableKey Key>
inline item_status item_remover<Key>::get_child_status(rb_item<Key> &item) {
  generical::byte child_status = item.left ? 1U : 0U;
  child_status += item.right ? 2U : 0U;
  switch (child_status) {
  case 1:
    return item_status::lchild;
  case 2:
    return item_status::rchild;
  case 3:
    return item_status::children;
  default:
    return item_status::none;
  }
}

template <ComparableKey Key>
inline void item_remover<Key>::visit(item_handle<Key> &root) {
  /*
  1. stack the branch with removing item
  1.1 from top to the removing item.
  1.1 include extened items which needs min cut to extend the branch.

  2. if to be removed item has:
  2.1 no children, then make it color = 2 and remove it after graft.
  2.2 single child, replace it with the child value and sum the color.

  2. if any node has color > 1, then apply removal graft.
  */
  auto branch = find_removing_branch(root);
  remove_from(std::move(branch));
  // make top black.
  if (root->color() == 0)
    root->increase_color();
}

template <ComparableKey Key>
inline branch_t<Key>
item_remover<Key>::find_removing_branch(item_handle<Key> &root) {
  branch_t<Key> branch_stack;

  branch_stack.push_front(root);

  while (branch_stack.front()) {
    decltype(auto) top = *branch_stack.front();
    if (to_remove_ < top.get_key())
      branch_stack.emplace_front(top.left);
    else if (top.get_key() < to_remove_)
      branch_stack.emplace_front(top.right);
    else {
      append_right_min(branch_stack);
      return std::move(branch_stack);
    }      
  }
  throw item_not_exists("can not find item with given key");
}

template <ComparableKey Key>
inline void item_remover<Key>::remove_from(branch_t<Key> branch) {
  auto removed = remove(branch.front());
  graft_branch(branch);
  removed_ = removed.release(); 
}

template <ComparableKey Key>
inline void item_remover<Key>::append_right_min(branch_t<Key> &branch) {
  auto to_remove = branch.front();
  auto status = get_child_status(*to_remove);
  if (status == item_status::children) {
    rb_item<Key> **next = &to_remove->right;
    while (*next) {
      branch.emplace_front(*next);
      next = &(*next)->left;
    }
    swap_value(*to_remove, *branch.front());
  }
}

template <ComparableKey Key>
inline item_handle<Key> item_remover<Key>::remove(item_handle<Key> &to_remove) {
  auto is_removing_black = to_remove->color() > 0;
  auto child_status = get_child_status(*to_remove);

  item_handle<Key> removed_handle(removed_);

  auto temp = &removed_handle;
  decltype(removed_) child = nullptr;

  switch (child_status) {
  case item_status::none:
    temp = &to_remove;
    break;
  case item_status::lchild:
    child = to_remove->left;
  case item_status::rchild:
    if (!child)
      child = to_remove->right;
    {
      auto removed = to_remove.set(child);
      temp->set(removed);
    }
    
    break;
  default:
    throw std::runtime_error("should not have two children");
  }
  //accumulate color to its child.
  if (is_removing_black)
    to_remove->increase_color();
  return *temp;
}

template <ComparableKey Key>
inline void item_remover<Key>::graft_branch(branch_t<Key> &branch) {
  branch.pop_front();
  while (!branch.empty() 
      && graft_for_removing(branch.front()))
    branch.pop_front();
}


} // namespace bbtree::algorithm