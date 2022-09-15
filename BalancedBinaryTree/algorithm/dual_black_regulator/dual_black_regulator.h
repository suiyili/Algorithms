#include "rb_node/rb_node.hpp"

using namespace btree::node;

namespace btree::algorithm {

template <comparable_key key_t_>
class dual_black_regulator final {
public:
  explicit dual_black_regulator(rb_node<key_t_>* dual_black_item, bool force = false);
  explicit dual_black_regulator(side x_side, bool force = false);
  bool regulate(rb_node<key_t_>*& parent);
  bool regulate(typename rb_node<key_t_>::shared_rb_node_t root, side parent_side);

private:
  static side get_side(rb_node<key_t_>* parent, rb_node<key_t_>* child);
  static bool is_black_raw(rb_node<key_t_>* item);
  static bool is_black(typename rb_node<key_t_>::shared_rb_node_t node);


  bool rotate_sibling_raw(rb_node<key_t_>*& parent, side x_side);
  bool rotate_sibling(typename rb_node<key_t_>::shared_rb_node_t root, side parent_side);

  rb_node<key_t_>* dual_black_item_;
  side x_side_;
  bool force_;
};

template <comparable_key key_t_>
dual_black_regulator(rb_node<key_t_> *)->dual_black_regulator<key_t_>;

} // namespace btree::algorithm