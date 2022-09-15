#pragma once

#include "trie/trie_node/trie_node.hpp"

namespace pattern_match::trie {
  class stem_node : public trie_node
  {
  public:
    explicit stem_node(char value);
    ~stem_node() override = default;

    bool is_leaf() const noexcept override;
    [[nodiscard]]size_t count_children() const noexcept override;
  
    trie_node* insert(trie_node_ptr node) override;

    trie_node* find(char key) override;

    trie_node* next_child() override;
  private:
    nodes children_;  
    typename nodes::iterator cursor_;
  };
}

