#pragma once

#include "domain_types.hpp"
#include "item_status.hpp"
#include "key_type.hpp"
#include <memory>

namespace bbtree::item {

template <ComparableKey Key> 
class rb_item final {
public:
  using value_type = Key;

  rb_item(std::unique_ptr<Key> key);

  ~rb_item() = default;

  Key &get_key();

  std::unique_ptr<Key> release_key();

  item_status red_status() const;

  generical::byte color() const;
  void increase_color();
  void pull_up_color();
  void push_down_color();

  rb_item *left;
  rb_item *right;

  template <ComparableKey Key>
  friend class item_handle;
  
  template <ComparableKey Key> 
  friend void swap_value(rb_item<Key>& left, rb_item<Key>& right);

private:
  bool check_red(rb_item *item) const;
  generical::byte &get_color(rb_item *child, generical::byte &dummy);
  generical::byte color_;

  std::unique_ptr<Key> key_;
};

template <ComparableKey Key>
rb_item(std::unique_ptr<Key> key)->rb_item<Key>;

} // namespace bbtree::item
