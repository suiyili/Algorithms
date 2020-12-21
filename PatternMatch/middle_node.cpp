#include "middle_node.hpp"

namespace pattern_match::trie{
  middle_node::middle_node(char value)
    :stem_node(value)
  {}
  bool middle_node::is_end() const noexcept
  {
    return false;
  }
}