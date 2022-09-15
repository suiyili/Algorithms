#include "rb_tree/tree_visitor_i.hpp"

namespace btree::algorithm {

template<comparable_key key_t_>
class node_inserter final : public tree_visitor_i<key_t_> {
public:
  template<typename ... key_args_>
  explicit node_inserter(key_args_&&... args);
  ~node_inserter() override;

  node_inserter(const node_inserter &other) = delete;
  node_inserter(node_inserter &&other) noexcept;
  node_inserter &operator=(const node_inserter &other) = delete;
  node_inserter &operator=(node_inserter &&other) = delete;
private:

  void visit_raw(rb_node<key_t_> *&root) override;
  branch_raw_t<key_t_> insert_to_branch_raw(rb_node<key_t_> *&root);
  void regulate_red_color(branch_raw_t<key_t_> branch);

  typename::rb_node<key_t_>::shared_rb_node_t visit(typename rb_node<key_t_>::shared_rb_node_t root) override;
  branch_t<key_t_> get_insert_branch(typename rb_node<key_t_>::shared_rb_node_t root);
  void regulate_red(branch_t<key_t_> branch);

  rb_node<key_t_>* to_insert_raw_;
  typename rb_node<key_t_>::shared_rb_node_t to_insert_;
  static constexpr side root_side_ = side::left;
};

} // namespace btree::algorithm