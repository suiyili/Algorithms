#pragma once

#include <memory>

namespace tree {

enum class side : bool { left = true, right = false };

class node_i {
public:
  virtual ~node_i() = default;
  virtual bool any_child() const = 0;
  [[nodiscard]] virtual node_i* put_child(side which, node_i* child) = 0;
  [[nodiscard]] virtual node_i *get_child(side which) = 0;
};
} // namespace tree
