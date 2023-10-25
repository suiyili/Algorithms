#include "rb_tree/tree_visitor_i.hpp"

namespace btree::algorithm {

template<comparable_key key_t_>
class node_inserter final : public tree_visitor_i<key_t_> {
public:
  template<typename ... key_args_>
  explicit node_inserter(key_args_&&... args);

  ~node_inserter() override = default;

  node_inserter(const node_inserter &other) = delete;
  node_inserter(node_inserter &&other) noexcept;

  node_inserter &operator=(const node_inserter &other) = delete;
  node_inserter &operator=(node_inserter &&other) = delete;
private:
  void visit(typename rb_node<key_t_>::node_handle_t &root) override;

  branch_stack_t<key_t_> get_insert_branch(typename rb_node<key_t_>::node_handle_t& root);
  void regulate_red(branch_stack_t<key_t_>& branch);
  static typename rb_node<key_t_>::shared_node_t get_top(branch_stack_t<key_t_>& stack_branch);

  const key_t_ to_insert_;
  static constexpr side root_side_ = side::left;
};

} // namespace btree::algorithm