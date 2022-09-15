#include "bit_tree.hpp"
#include "generic/bit_tree_types.hpp"
#include <stack>

using namespace tree::generic;

namespace tree {

bool bit_tree_algo::add(int key, node_i* value) {
  bool changed = false;
  bitset_int bits(key);
  node_i *parent = &root_;
  for (auto i : get_bit_indices()) {
    auto which = bits[i] ? side::right : side::left;
    auto child = parent->get_child(which);
    if (!child) {
      child = i == 0 ? value : new bit_node();
      parent->put_child(which, child);
      changed = true;
    }
    parent = child;
  }
  return changed;
}

node_i* bit_tree_algo::get(int key) {
  bitset_int bits(key);
  node_i* parent = &root_;
  for (auto i : get_bit_indices()) {
    auto which = bits[i] ? side::right : side::left;
    parent = parent->get_child(which);
    if (!parent)
      break;
  }
  return parent;
}

node_i* bit_tree_algo::remove(int key) {
  bitset_int bits(key);
  node_i* parent = &root_;
  std::stack<std::pair<node_i*, side>> branch;
  
  for (auto i : get_bit_indices()) {
    auto which = bits[i] ? side::right : side::left;
    //bottom leaf will not be in branch.
    branch.emplace(parent, which);
    parent = parent->get_child(which);
    if (!parent)
      return nullptr;
  }
  
  while(!branch.empty()) {
    auto& [top, which] = branch.top();
    auto child = top->put_child(which, nullptr);
    if (child != parent)
      delete child;
    branch.pop();
    if (top->any_child())
      break;
  };
  
  return parent;
}

} // namespace tree