#include "tree_visitor_i.hpp"

namespace bbtree::algorithm {

template<ComparableKey Key>
class item_inserter final : public tree_visitor_i<Key> {
public:
  item_inserter(std::unique_ptr<Key> key);

  item_inserter(const item_inserter &other) = delete;
  item_inserter(item_inserter &&other) noexcept;
  item_inserter &operator=(const item_inserter &other) = delete;
  item_inserter &operator=(item_inserter &&other) = delete;

private:
  void visit(item_handle<Key> &root) override;
  branch_t<Key> find_insert_branch(item_handle<Key> &root);
  void insert_into(branch_t<Key> branch);

  std::unique_ptr<Key> to_insert_;
};

template <ComparableKey Key>
item_inserter(std::unique_ptr<Key> key)->item_inserter<Key>;
} // namespace bbtree::algorithm