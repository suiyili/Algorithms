#include "mock_node.hpp"

namespace tree {

bool mock_node::any_child() const noexcept { return false; }
node_i* mock_node::put_child(side which, node_i* child) noexcept
{
    return nullptr;
}
node_i *mock_node::get_child(side which) noexcept { return nullptr; }
} // namespace tree