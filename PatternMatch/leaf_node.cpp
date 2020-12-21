#include "leaf_node.hpp"

namespace pattern_match::trie {
leaf_node::leaf_node(char value) : trie_node(value) {}
bool leaf_node::is_end() const noexcept { return true; }
bool leaf_node::is_leaf() const noexcept { return true; }
size_t leaf_node::count_children() const noexcept { return 1U; }
trie_node* leaf_node::insert(trie_node_ptr key) { return nullptr; }
trie_node* leaf_node::find(char key) { return nullptr; }
trie_node* leaf_node::next_child() { return nullptr; }
}  // namespace pattern_match::trie