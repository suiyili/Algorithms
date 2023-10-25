#pragma once

#include <rb_node/rb_node.hpp>
using namespace btree::node;

namespace btree {

template<comparable_key key_t_>
class tree_visitor_i {
public:
  virtual ~tree_visitor_i() = default;
  virtual void visit(typename rb_node<key_t_>::node_handle_t& root) = 0;
};

} // namespace btree