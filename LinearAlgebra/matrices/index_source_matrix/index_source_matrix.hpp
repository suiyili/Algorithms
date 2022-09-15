#pragma once

#include "matrices/index_matrix_i.hpp"

namespace algebra::matrices {
class index_source_matrix final: public index_matrix_i {
 public:
  index_source_matrix(size_t columns, size_t rows);
  
  virtual size_t rows() const override;
  virtual size_t columns() const override;
  virtual pixel operator[](const pixel& id) const override;

 private:
  const size_t columns_, rows_;
};
}

