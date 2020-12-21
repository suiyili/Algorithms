#pragma once

#include "stem_node.hpp"

namespace pattern_match::trie {

  class end_node : public stem_node
  {
  public:
    explicit end_node(char value);

    bool is_end() const noexcept override;
  };

}