#pragma once

#include "node/node_i.hpp"
#include "generic/resource_manager/resource_manager.hpp"
#include <stdexcept>

using namespace tree::generic;

namespace tree {

template <typename T> class leaf_node final : public node_i {
public:
  leaf_node(T *value);
  T *get_value();
  static void* operator new(std::size_t size);
  static void operator delete(void* p);

private:
  bool any_child() const noexcept override;
  node_i *put_child(side which, node_i *child) noexcept override;
  node_i *get_child(side which) noexcept override;

  T *value_;
};

template <typename T> leaf_node(T *value) -> leaf_node<T>;

template <typename T>
inline leaf_node<T>::leaf_node(T *value) : value_(value) {}

template <typename T> inline T *leaf_node<T>::get_value() { return value_; }

template<typename T>
inline void* leaf_node<T>::operator new(std::size_t size)
{
  return manager.allocate(size);
}

template<typename T>
inline void leaf_node<T>::operator delete(void* p)
{
  manager.deallocate(p, sizeof(leaf_node));
}

template <typename T> inline bool leaf_node<T>::any_child() const noexcept {
  return false;
}

template <typename T>
inline node_i *leaf_node<T>::put_child(side which, node_i *child) noexcept {
  return child;
}

template <typename T>
inline node_i *leaf_node<T>::get_child(side which) noexcept {
  return nullptr;
}

} // namespace tree