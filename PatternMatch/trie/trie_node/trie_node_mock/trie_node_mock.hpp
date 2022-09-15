#pragma once

#include "trie/trie_node/trie_node.hpp"

namespace pattern_match::trie {
class trie_node_mock : public trie_node {

public:
  trie_node_mock(char c);

  bool is_end() const noexcept override;
  bool is_leaf() const noexcept override;
  size_t count_children() const noexcept override;

  trie_node* insert(trie_node_ptr node) override;

  trie_node* find(char key) override;

  trie_node* next_child() override;
};
}  // namespace pattern_match::trie
