#include "rb_tree.h"

namespace bbtree {

template <ComparableKey Key> inline rb_tree<Key>::rb_tree() : root_(nullptr) {}

template <ComparableKey Key> inline rb_tree<Key>::~rb_tree() {
  clear(root_);
  return;
}

template <ComparableKey Key>
inline rb_tree<Key>::rb_tree(rb_tree<Key> &&other) : root_(other.root_) {
  other.root_ = nullptr;
}

template <ComparableKey Key>
inline bool rb_tree<Key>::contains(const Key &key) {
  auto cur = root_;
  while (cur != nullptr) {
    decltype(auto) k = cur->get_key();
    if (key < k)
      cur = cur->left;
    else if (k < key)
      cur = cur->right;
    else
      return true;
  }
  return false;
}

template <ComparableKey Key>
inline void rb_tree<Key>::accept(tree_visitor_i<Key> &visitor) {
  item_handle root(root_);
  visitor.visit(root);
}

template <ComparableKey Key>
inline void rb_tree<Key>::clear(rb_item<Key> *to_clear) {
  if (to_clear) {
    clear(to_clear->left);
    clear(to_clear->right);
    delete to_clear;
  }
}

} // namespace bbtree