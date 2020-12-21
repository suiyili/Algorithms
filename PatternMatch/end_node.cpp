#include "end_node.hpp"

namespace pattern_match::trie{
  end_node::end_node(char value)
    :stem_node(value)
  { }
  bool end_node::is_end() const noexcept
  {
    return true;
  }
}