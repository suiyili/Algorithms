#include "rb_tree.h"
#include <atomic>

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

template <comparable_key key_t_>
inline void rb_tree<key_t_>::accept(tree_visitor_i<key_t_> &visitor) {
  visitor.visit(root_);
}
} // namespace btree