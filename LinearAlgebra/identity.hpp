#pragma once

#include "identity.h"

namespace algebra::arithmetic {

template <typename T>
inline matrix<T> make_identity(size_t size) {
  matrix<T> m(size);
  for (size_t i = 0U; i < size; ++i) {
    for (size_t j = 0U; j < size; ++j) {
      pixel id{i, j};
      if (i == j) m[id] = one<T>;
    }
  }
  return m;
}

}  // namespace algebra::arithmetic
