#include <rb_node/rb_node.hpp>

using namespace btree::node;

namespace btree::algo {

template<comparable_key key_t_>
[[nodiscard]] branch_stack_t<key_t_> insert_node(typename rb_node<key_t_>::node_handle_t& root,
                                                 std::unique_ptr<rb_node<key_t_>> to_insert);

} // namespace btree::algo