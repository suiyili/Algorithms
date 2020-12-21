#pragma once

#include "rb_item.hpp"
#include "tree_visitor_i.hpp"

namespace bbtree {

template <ComparableKey Key> class rb_tree final {
public:
  rb_tree();
  ~rb_tree();

  rb_tree(const rb_tree<Key> &) = delete;
  rb_tree(rb_tree<Key> &&other);

  rb_tree<Key> &operator=(const rb_tree<Key> &) = delete;

  bool contains(const Key& key);

  void accept(tree_visitor_i<Key> &visitor);

private:
  void clear(rb_item<Key> *to_clear);
#ifdef TEST
public:
#endif
  rb_item<Key> *root_;
};

} // namespace bbtree