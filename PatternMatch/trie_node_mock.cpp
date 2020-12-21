#ifdef TEST

#include "trie_node_mock.hpp"

#include <stdexcept>

namespace pattern_match::trie {
trie_node_mock::trie_node_mock(char c) : trie_node(c) {}
bool trie_node_mock::is_end() const noexcept { return false; }
bool trie_node_mock::is_leaf() const noexcept { return false; }
size_t trie_node_mock::count_children() const noexcept { return 0; }
trie_node* trie_node_mock::insert(trie_node_ptr node) {
  throw std::logic_error("not supported");
}
trie_node* trie_node_mock::find(char key) {
  throw std::logic_error("not supported");
}
trie_node* trie_node_mock::next_child() { return nullptr; }
}  // namespace pattern_match::trie

#endif  // TEST