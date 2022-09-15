#pragma once

#include <cctype>
#include "node/leaf_node/leaf_node.hpp"

namespace tree {
class bit_node final : public node_i {
public:
  ~bit_node() override;
  static void* operator new(std::size_t size);
  static void operator delete(void* p);

private:
  bool any_child() const noexcept override;
  node_i *put_child(side which, node_i *child) noexcept override;
  node_i *get_child(side which) noexcept override;
  
  node_i *left_ = nullptr, *right_ = nullptr;
};
} // namespace tree