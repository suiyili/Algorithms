#pragma once

#include "node/bit_node/bit_node.hpp"
#include "node/leaf_node/leaf_node.hpp"

namespace tree {
class bit_tree_algo final {
public:
  bit_tree_algo() = default;
  bit_tree_algo(const bit_tree_algo &other) = delete;
  bit_tree_algo(bit_tree_algo &&other) = delete;
  bit_tree_algo &operator=(const bit_tree_algo &other) = delete;
  bit_tree_algo &operator=(bit_tree_algo &&other) = delete;

  bool add(int key, node_i *value);
  node_i *get(int key);
  node_i *remove(int key);

private:
  bit_node root_;
};

//////////////////////////////////////////

template <typename T> class bit_tree final {
public:
  bool add(int key, T *value);
  T *get(int key);
  T *remove(int key);

private:
  bit_tree_algo tree_;
};

template<typename T>
inline bool bit_tree<T>::add(int key, T* value) {
  return tree_.add(key, new leaf_node(value));
}

template<typename T>
inline T* bit_tree<T>::get(int key)
{
  T* value = nullptr;
  auto leaf = dynamic_cast<leaf_node<T>*>(tree_.get(key));
  if (leaf)
    value = leaf->get_value();
  return value;
}

template<typename T>
inline T* bit_tree<T>::remove(int key) {
  T* value = nullptr;
  auto leaf = dynamic_cast<leaf_node<T>*>(tree_.remove(key));
  if(leaf) {
    value = leaf->get_value();
    delete leaf;
  }
  return value;
}

} // namespace tree
