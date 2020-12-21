#pragma once

namespace bbtree {
template <typename Key> 
concept ComparableKey = requires(Key k1, Key k2) {
  k1 < k2;
  k1 == k2;
  !(k1 < k2);
  !(k1 == k2);
  //k1 <=> k2;
};
} // namespace bbtree
