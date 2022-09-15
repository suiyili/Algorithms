#include "bit_node.hpp"
#include "generic/resource_manager/resource_manager.hpp"
#include <stdexcept>

using namespace tree::generic;
namespace tree {

bit_node::~bit_node() {
  delete left_;
  delete right_;
}

void* bit_node::operator new(std::size_t size)
{
  return manager.allocate(size);
}

void bit_node::operator delete(void* p)
{
  manager.deallocate(p, sizeof(bit_node));
}

bool bit_node::any_child() const noexcept { return left_ || right_; }

node_i *bit_node::put_child(side which, node_i *child) noexcept {
  decltype(left_) &c = which == side::left ? left_ : right_;
  auto prev = c;
  c = child;
  return prev;
}

node_i *bit_node::get_child(side which_child) noexcept {
  return which_child == side::left ? left_ : right_;
}

} // namespace tree