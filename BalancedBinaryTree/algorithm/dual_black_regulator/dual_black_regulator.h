#include "rb_node/rb_node.hpp"

using namespace btree::node;

namespace btree::algorithm {

template <comparable_key key_t_>
class dual_black_regulator final {
public:
  explicit dual_black_regulator(side x_side);
  bool regulate(typename rb_node<key_t_>::node_handle_t& root, side which);
private:
  static bool is_black(const typename rb_node<key_t_>::shared_node_t& node);

  bool rotate_sibling(typename rb_node<key_t_>::node_handle_t& root, side which);
  side x_side_;
};

} // namespace btree::algorithm