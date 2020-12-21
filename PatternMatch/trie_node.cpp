#include "trie_node.hpp"
namespace pattern_match::trie {
trie_node::trie_node(char value) : value_(value) {}

trie_node::operator char() const noexcept { return value_; }

bool operator==(trie_node_ptr const& lhs, trie_node_ptr const& rhs) {
  return (char)(*lhs) == (char)(*rhs);
}

}  // namespace pattern_match::trie

namespace std {
std::size_t hash<trie_node_ptr>::operator()(
    trie_node_ptr const& node) const noexcept {
  return std::hash<char>{}((char)(*node));
}
}  // namespace std
