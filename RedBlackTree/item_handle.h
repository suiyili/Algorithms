#include "rb_item.hpp"
#include <type_traits>

namespace bbtree::item {

enum class child_side : char { left = -1, right = 1 };

template <ComparableKey Key> 
class item_handle final {
public:
  item_handle(rb_item<Key> *&item);
  ~item_handle() = default;

  item_handle(const item_handle &other);
  item_handle(item_handle &&other);
  item_handle &operator=(const item_handle &other) = delete;
  item_handle &operator=(item_handle &&other) = delete;

  void rotate();

  rb_item<Key> *operator->();
  rb_item<Key> &operator*();
  operator bool() const;
  
  rb_item<Key> *set(rb_item<Key> *item);
  rb_item<Key> *release();

private:
  static void check(rb_item<Key> *item);
  void left_rotate();
  void right_rotate();

  rb_item<Key> *&item_;
};

template <ComparableKey Key> 
item_handle(rb_item<Key>*& item)->item_handle<Key>;

} // namespace bbtree::item