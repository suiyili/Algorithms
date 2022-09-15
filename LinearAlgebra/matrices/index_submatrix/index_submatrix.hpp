#pragma once

#include "matrices/index_matrix_i.hpp"

namespace algebra::matrices {

class index_submatrix final: public index_matrix_i {
 public:
  index_submatrix(const index_matrix_i &source, const pixel& cross);

  index_submatrix(const index_submatrix &) = delete;
  index_submatrix(index_submatrix &&) = delete;

  virtual size_t rows() const override;
  virtual size_t columns() const override;

  virtual pixel operator[](const pixel &id) const override;

 private:
  static size_t find_subordinal(size_t ordinal, size_t size);
  const index_matrix_i &source_;
  const pixel cross_;
};

}  // namespace algebra::matrices