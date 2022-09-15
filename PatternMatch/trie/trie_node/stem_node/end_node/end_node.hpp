#pragma once

#include "trie/trie_node/stem_node/stem_node.hpp"

namespace pattern_match::trie {

  class end_node : public stem_node
  {
  public:
    explicit end_node(char value);

    bool is_end() const noexcept override;
  };

}