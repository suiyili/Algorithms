#pragma once

#include "../rb_node/rb_node.hpp"
using namespace btree::node;

namespace btree {

template<comparable_key key_t_>
class tree_visitor_i {
public:
  virtual ~tree_visitor_i() = default;
  virtual void visit_raw(rb_node<key_t_> *&root) = 0;
  virtual typename::rb_node<key_t_>::shared_rb_node_t visit(typename::rb_node<key_t_>::shared_rb_node_t root) = 0;
};

} // namespace btree