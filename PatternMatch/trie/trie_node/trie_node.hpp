#pragma once

#include <string_view>
#include <memory>
#include "generic/pattern_match_types.hpp"

namespace pattern_match::trie {

class trie_node;
using trie_node_ptr = std::unique_ptr<trie_node>;

class trie_node {
 public:
  explicit trie_node(char value);
  virtual ~trie_node() noexcept = default;

  explicit operator char() const noexcept;

  virtual bool is_end() const noexcept = 0;
  virtual bool is_leaf() const noexcept = 0;
  virtual size_t count_children() const noexcept = 0;

  virtual trie_node* insert(trie_node_ptr node) = 0;
  virtual trie_node* find(char key) = 0;
  virtual trie_node* next_child() = 0;

 private:
  const char value_;
};

bool operator==(trie_node_ptr const& lhs, trie_node_ptr const& rhs);

}  // namespace pattern_match::trie

namespace std {

using namespace pattern_match::trie;
template <>
struct hash<trie_node_ptr> {
  std::size_t operator()(trie_node_ptr const& s) const noexcept;
};

}  // namespace std

namespace pattern_match::trie {

using nodes = pmr_hash_set<trie_node_ptr>;
using node_cursor = nodes::const_iterator;
}  // namespace pattern_match
