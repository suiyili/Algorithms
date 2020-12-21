#pragma once

#include "stem_node.hpp"

namespace pattern_match::trie {

  class middle_node final: public stem_node
  {
  public:
    explicit middle_node(char value);

    bool is_end() const noexcept override;

  };

}