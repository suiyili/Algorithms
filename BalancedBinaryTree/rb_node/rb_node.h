#pragma once

#include "generic/key_type.hpp"
#include <memory>
#include <stack>
#include <memory>

using namespace btree::generic;

namespace btree::node {

enum class side : bool {
  left = true,
  right = false,
};

static side opposite(side which);

template<comparable_key key_t_>
class rb_node final {
public:
  using value_type_t = key_t_;
  using shared_rb_node_t = std::shared_ptr<rb_node<key_t_>>;

  template<typename... _key_args>
  explicit rb_node(_key_args &&... args);

  ~rb_node() = default;

  static void *operator new(std::size_t size);
  static void operator delete(void *p);

  explicit operator key_t_ &();

  [[nodiscard]] std::uint8_t color() const;
  void increase_color();
  bool decrease_color();

  void pull_up_color_raw();
  void push_down_color_raw();

  void pull_up_color();
  void push_down_color();

  rb_node *&get_raw_child(side which);
  shared_rb_node_t get_child(side which);
  void set_child(shared_rb_node_t child, side which);
  void rotate(side parent_side, side child_side);

private:
  using atomic_shared_rb_node_t = std::atomic<shared_rb_node_t>;
  atomic_shared_rb_node_t& get_child_ref(side which);

  void pull_up_color_raw(rb_node *child);
  void push_down_color_raw(rb_node *child);

  void pull_up_color(shared_rb_node_t child);
  void push_down_color(shared_rb_node_t child);

  key_t_ key_;
  unsigned char color_ = 0U;
  rb_node *left_ = nullptr;
  rb_node *right_ = nullptr;
  atomic_shared_rb_node_t atomic_left_;
  atomic_shared_rb_node_t atomic_right_;
};

template<comparable_key key_t_>
void rotate_raw(rb_node<key_t_> *&item, side which);

template<comparable_key key_t_>
using branch_raw_t = std::stack<std::reference_wrapper<rb_node<key_t_> *>>;

template<comparable_key key_t_>
using branch_t = std::stack<std::pair<typename rb_node<key_t_>::shared_rb_node_t, side>>;

} // namespace btree::node
