#pragma once

#include "generic/algebra_types.hpp"

using namespace algebra::generic;

namespace algebra::matrices {
class index_matrix_i {
 public:
  virtual ~index_matrix_i() = default;
  virtual size_t rows() const = 0;
  virtual size_t columns() const = 0;
  virtual pixel operator[](const pixel& id) const= 0;
};
}

