#include <rb_node/rb_node.hpp>

using namespace btree::node;

namespace btree::algo {

template<comparable_key key_t_>
class scope_node_remover final {
public:
  explicit scope_node_remover(branch_stack_t<key_t_> branch);
  ~scope_node_remover();

  branch_stack_t<key_t_>& get_branch();
private:
  branch_stack_t<key_t_> branch_;
  typename rb_node<key_t_>::node_handle_t* to_remove_ = nullptr;
};

template<comparable_key key_t_>
static scope_node_remover<key_t_> remove_node(typename rb_node<key_t_>::node_handle_t& root, const key_t_& to_remove);

} // namespace btree::algo