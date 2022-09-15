#pragma once

#include <unordered_set>
#include "tree_retriever/tree_retriever.hpp"
#include "generic/tree_type.hpp"

using namespace tree::generic;

namespace tree::spanning_tree {

  enum class spanning_type : char
  {
    maximum = 1,
    minimum = -1
  };

  using connect_set = std::pmr::unordered_set<connect>;

  connect_set get_spanning_tree(const tree_retriever& tree, spanning_type type);

}  // namespace tree::spanning_tree
