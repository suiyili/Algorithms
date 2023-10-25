#pragma once

#include <rb_node/rb_node.hpp>
#include "tree_visitor_i.hpp"
#include <memory>

namespace btree {

template<comparable_key key_t_> class rb_tree final {
public:
  rb_tree() = default;
  ~rb_tree() = default;

  rb_tree(const rb_tree<key_t_> &) = delete;
  rb_tree(rb_tree<key_t_> &&other) noexcept;

  rb_tree<key_t_> &operator=(const rb_tree<key_t_> &) = delete;

  bool contains(const key_t_ &key);

  void accept(tree_visitor_i<key_t_> &visitor);

private:
#ifdef TEST
public:
#endif
  typename node::rb_node<key_t_>::node_handle_t root_;
};

} // namespace btree