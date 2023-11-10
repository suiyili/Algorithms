#include "rb_tree.h"
#include <algo/insert_node/insert_node.hpp>
#include <algo/remove_node/remove_node.hpp>
#include <algo/regulate_red/regulate_red.hpp>
#include <algo/regulate_black/regulate_black.hpp>
#include <atomic>

using namespace btree::algo;

namespace btree {

template <comparable_key key_t_>
inline rb_tree<key_t_>::rb_tree(rb_tree<key_t_> &&other) noexcept
: root_(other.root_.exchange(nullptr, std::memory_order_relaxed)) {
}

template <comparable_key key_t_>
inline bool rb_tree<key_t_>::contains(const key_t_ &key) {
  auto cur = root_.load(std::memory_order_relaxed);
  while (cur) {
    auto & cur_key = (const key_t_&)*cur;
    if (key < cur_key)
      cur = cur->get_child(side::left);
    else if (cur_key < key)
      cur = cur->get_child(side::right);
    else
      return true;
  }
  return false;
}

template<comparable_key key_t_>
template<typename... args_>
void rb_tree<key_t_>::insert(args_ &&... args) {
  auto branch = insert_node(root_, std::make_unique<rb_node<key_t_>>(std::forward<args_>(args)...));
  regulate_red<key_t_>(branch);
}

template<comparable_key key_t_>
void rb_tree<key_t_>::remove(const key_t_ key) {
  auto remover = remove_node(root_, key);
  regulate_black<key_t_>(remover.get_branch());
}

} // namespace btree