#include "rb_node/rb_node.hpp"
#include <stack>

using namespace btree::node;

namespace btree::algorithm {

template <comparable_key key_t_> class consecutive_red_regulator final {
public:
  consecutive_red_regulator();
  bool regulate_raw(rb_node<key_t_> *&parent);
  bool regulate(typename rb_node<key_t_>::shared_rb_node_t root, side parent_side);

private:
  static side get_child_side_raw(rb_node<key_t_>* parent, rb_node<key_t_>* child);
  [[nodiscard]] bool reach_limit() const;
  rb_node<key_t_> **chain_old_[2];
  std::stack<side> child_route_;
  std::uint8_t count_;
};

} // namespace btree::algorithm