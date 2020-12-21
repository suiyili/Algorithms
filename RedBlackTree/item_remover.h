#include "tree_visitor_i.hpp"

namespace bbtree::algorithm {

template<ComparableKey Key>
class item_remover final : public tree_visitor_i<Key> {
public:
  item_remover(const Key &key_to_remove);
  ~item_remover();

private:
  static item_status get_child_status(rb_item<Key>& item);

  void visit(item_handle<Key> &root) override;
  branch_t<Key> find_removing_branch(item_handle<Key> &root);
  void remove_from(branch_t<Key> branch);

  void append_right_min(branch_t<Key>& branch);

  
  item_handle<Key> remove(item_handle<Key> &parent);
  void graft_branch(branch_t<Key>& branch);

  const Key &to_remove_;
  rb_item<Key> *removed_;
};

template <ComparableKey Key>
item_remover(const Key &key_to_remove)->item_remover<Key>;

} // namespace bbtree::algorithm