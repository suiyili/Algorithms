#include <rb_node/rb_node.hpp>

using namespace btree::node;

namespace btree::algo {

template <comparable_key key_t_>
void regulate_black(branch_stack_t<key_t_>& branch);

} // namespace btree::algo