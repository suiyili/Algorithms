#include "rb_tree.h"

namespace btree {

template <comparable_key key_t_> inline rb_tree<key_t_>::rb_tree() : root_raw_(nullptr) {}

template <comparable_key key_t_> inline rb_tree<key_t_>::~rb_tree() {
  clear(root_raw_);
  return;
}

template <comparable_key key_t_>
inline rb_tree<key_t_>::rb_tree(rb_tree<key_t_> &&other) : root_raw_(other.root_raw_) {
  other.root_raw_ = nullptr;
}

template <comparable_key key_t_>
inline bool rb_tree<key_t_>::contains(const key_t_ &key) {
  auto cur = root_raw_;
  while (cur != nullptr) {
    auto & cur_key = (const key_t_&)*cur;
    if (key < cur_key)
      cur = cur->get_raw_child(side::left);
    else if (cur_key < key)
      cur = cur->get_raw_child(side::right);
    else
      return true;
  }
  return false;
}

template <comparable_key key_t_>
inline void rb_tree<key_t_>::accept(tree_visitor_i<key_t_> &visitor) {
  visitor.visit_raw(root_raw_);
}

template <comparable_key key_t_>
inline void rb_tree<key_t_>::clear(rb_node<key_t_> *to_clear) {
  if (to_clear) {
    clear(to_clear->get_raw_child(side::left));
    clear(to_clear->get_raw_child(side::right));
    delete to_clear;
  }
}

} // namespace btree