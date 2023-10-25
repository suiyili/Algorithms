#pragma once

#include "generic/key_type.hpp"
#include <memory>
#include <stack>
#include <memory>
#include <cstdint>
#include <functional>

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
  using shared_node_t = std::shared_ptr<rb_node<key_t_>>;
  using node_handle_t = std::atomic<shared_node_t>;

  template<typename... key_args>
  explicit rb_node(key_args &&... args);

  ~rb_node() = default;

  static void *operator new(std::size_t size);
  static void operator delete(void *p);

  explicit operator key_t_ &();

  [[nodiscard]] std::uint8_t color() const;
  void increase_color();
  void decrease_color();

  void pull_up_color();
  void push_down_color();

  shared_node_t get_child(side which);
  void set_child(shared_node_t child, side which);
  node_handle_t &get_child_handle(side which);

  template<typename k_t_>
  friend void rotate(std::atomic<std::shared_ptr<rb_node<k_t_>>>& parent, side which);
private:

  key_t_ key_;
  unsigned char color_ = 0U;
  node_handle_t atomic_left_;
  node_handle_t atomic_right_;
};

template<comparable_key key_t_>
using branch_stack_t = std::stack<std::pair<std::reference_wrapper<typename rb_node<key_t_>::node_handle_t>, side>>;

} // namespace btree::node
