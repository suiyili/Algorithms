#include "rb_node/rb_node.hpp"
#include <stack>

using namespace btree::node;

namespace btree::algorithm {

template <comparable_key key_t_> class consecutive_red_regulator final {
public:
  consecutive_red_regulator() = default;
  bool regulate(typename rb_node<key_t_>::node_handle_t& handle, side which);

private:
  [[nodiscard]] bool reach_limit() const;
  std::stack<side> child_route_;
};

} // namespace btree::algorithm