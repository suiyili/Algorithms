#pragma once

#include "trie/trie_node/trie_node.hpp"

namespace pattern_match::trie {

class leaf_node final : public trie_node {
 public:
  explicit leaf_node(char value);
  ~leaf_node() override = default;

  bool is_end() const noexcept override;
  bool is_leaf() const noexcept override;
  size_t count_children() const noexcept override;
  
  trie_node* insert(trie_node_ptr node) override;

  trie_node* find(char key) override;

  trie_node* next_child() override;

};

}  // namespace pattern_match::trie