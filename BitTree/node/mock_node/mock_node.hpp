#pragma once

#include "node/node_i.hpp"

namespace tree {
class mock_node final: public node_i
{
public:
  bool any_child() const noexcept override;
  node_i* put_child(side which, node_i* child) noexcept override;
  node_i* get_child(side which)  noexcept override;
};
}


