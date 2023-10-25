#include "rb_tree/tree_visitor_i.hpp"

namespace btree::algorithm {

template<comparable_key key_t_>
class node_remover final : public tree_visitor_i<key_t_> {
public:
  template<typename ... key_args_>
  explicit node_remover(key_args_&&... args);
  ~node_remover() = default;

private:
  void visit(typename rb_node<key_t_>::node_handle_t &root) override;

  branch_stack_t<key_t_> make_removing_branch(typename rb_node<key_t_>::node_handle_t& root);
  void append_right_min(branch_stack_t<key_t_>& branch);
  bool remove(typename rb_node<key_t_>::node_handle_t& handle);
  static bool both_children_available(const typename rb_node<key_t_>::shared_node_t& parent);

  const key_t_ to_remove_;
  static constexpr side root_side_ = side::left;
};

template <comparable_key key_t_>
node_remover(const key_t_ &key_to_remove)->node_remover<key_t_>;

} // namespace btree::algorithm