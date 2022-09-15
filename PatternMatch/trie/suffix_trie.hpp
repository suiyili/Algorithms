#pragma once

#include <string_view>
#include "trie/trie_node/trie_node.hpp"

namespace pattern_match::trie {

class suffix_trie {

public:
  suffix_trie(std::string_view pattern);
  ~suffix_trie() = default;

  bool contains(std::string_view target);
  size_t find(std::string_view target);
  size_t counts(std::string_view target);
  std::pair<size_t, size_t> get_longest_repeat();
  std::pair<size_t, size_t> find_longest_match(std::string_view target);

private:
  static resource_manager resource;
  static trie_node_ptr build_trie(std::string_view pattern);
  static trie_node* add_child(char child, bool is_end, trie_node* parent);
  static size_t get_max_depth(trie_node* root);

  trie_node* find_node(std::string_view target);

  std::string_view pattern_;
  trie_node_ptr root_;
};

}  // namespace pattern_match::trie