#pragma once

#include "generic/tree_type.hpp"

using namespace tree::generic;

namespace tree::spanning_tree {
class tree_retriever {

public:
  explicit tree_retriever(std::size_t size);
  void set(const connect& conn, std::size_t weight);
  std::size_t get_weight(const connect& conn) const;
  node_vector get_connected_nodes(std::size_t node) const;
  std::size_t size() const noexcept;

private:
  static std::size_t check_size(std::size_t size);
  bool includes(const connect& conn) const;  
  std::size_t to_ordinal(const connect& conn) const;

  const std::size_t size_;
  node_vector matrix_;
};
}  // namespace tree
