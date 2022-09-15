#include "stem_node.hpp"
#include "trie/trie_node/leaf_node/leaf_node.hpp"

namespace pattern_match::trie{
  stem_node::stem_node(char value)
    :trie_node(value), cursor_(children_.begin())
  {}

  bool stem_node::is_leaf() const noexcept
  {
    return false;
  }

  [[nodiscard]] size_t stem_node::count_children() const noexcept
  {
    return children_.size() + is_end();
  }

  trie_node* stem_node::insert(trie_node_ptr node)
  {
    children_.erase(node);
    auto inserted = children_.insert(std::move(node));
    cursor_ = children_.begin();
    return inserted.first->get();
  }
  trie_node* stem_node::find(char key)
  {
    std::unique_ptr<trie_node> leaf = std::make_unique<leaf_node>(key);
    auto found = children_.find(leaf);
    return found == children_.end() ? nullptr : found->get();
  }
  trie_node* stem_node::next_child()
  {
    trie_node* child = nullptr;
    if (cursor_ == children_.end())
      cursor_ = children_.begin();
    else
      child = (cursor_++)->get();
    return child;
  }
}