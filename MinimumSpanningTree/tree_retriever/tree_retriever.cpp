#include "tree_retriever.hpp"

#include "generic/resource_manager/resource_manager.hpp"

namespace tree::spanning_tree {
tree_retriever::tree_retriever(std::size_t size)
    : size_(check_size(size)),
      matrix_(resource_manager::get_allocator<typename decltype(
                  matrix_)::value_type>()) {
  std::size_t len = size_ * (size_ + 1) / 2;
  matrix_.resize(len, 0U);
}

void tree_retriever::set(const connect& conn, std::size_t weight) {
  if (includes(conn)) {
    auto i = to_ordinal(conn);
    matrix_[i] = weight;
  }
}

std::size_t tree_retriever::get_weight(const connect& conn) const {
 
  if (!includes(conn)) return 0U;

  auto i = to_ordinal(conn);
  return matrix_[i];
}

node_vector tree_retriever::get_connected_nodes(std::size_t node) const {
  node_vector nodes(resource_manager::get_allocator<size_t>());

  for (size_t i = 0; i < size_ + 1; ++i) {
    if (get_weight({node, i}) > 0) nodes.push_back(i);
  }
  return nodes;
}

std::size_t tree_retriever::size() const noexcept { return size_ + 1; }

std::size_t tree_retriever::check_size(std::size_t size) {
  // triagle metrix excluding dialog
  if (size < 2) throw std::logic_error("size is less than 2");
  return size - 1;
}

bool tree_retriever::includes(const connect& conn) const {
  auto reverse_row = size_ < conn.from() ? size_ : size_ - conn.from();
  auto col = conn.to();

  return reverse_row + col < size_;
}

std::size_t tree_retriever::to_ordinal(const connect& conn) const {
  return conn.from() * (conn.from() - 1) / 2 + conn.to();
}

}  // namespace tree::spanning_tree
