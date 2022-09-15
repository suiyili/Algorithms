#include "rb_tree/tree_visitor_i.hpp"

namespace btree::algorithm {

template<comparable_key key_t_>
class node_remover final : public tree_visitor_i<key_t_> {
public:
  explicit node_remover(const key_t_ &key_to_remove);
  ~node_remover() = default;

private:
  typename rb_node<key_t_>::shared_rb_node_t visit(typename rb_node<key_t_>::shared_rb_node_t root) override;

  void visit_raw(rb_node<key_t_> *&root) override;
  
  branch_raw_t<key_t_> find_removing_branch_raw(rb_node<key_t_> *&root);
  branch_t<key_t_> find_removing_branch(typename rb_node<key_t_>::shared_rb_node_t root);
  void append_right_min_raw(branch_raw_t<key_t_>& branch);
  void append_right_min(branch_t<key_t_>& branch);
  rb_node<key_t_>* remove_raw(rb_node<key_t_> *&item);
  static bool both_children_available_raw(rb_node<key_t_>& parent);
  static bool both_children_available(typename rb_node<key_t_>::shared_rb_node_t parent);
  static rb_node<key_t_>* get_single_child(rb_node<key_t_>& parent);

  const key_t_ &to_remove_;
  static constexpr side root_side_ = side::left;
};

template <comparable_key key_t_>
node_remover(const key_t_ &key_to_remove)->node_remover<key_t_>;

} // namespace btree::algorithm