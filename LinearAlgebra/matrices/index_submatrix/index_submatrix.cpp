#include "index_submatrix.hpp"

namespace algebra::matrices {

index_submatrix::index_submatrix(const index_matrix_i &source,
                                 const pixel &cross)
    : source_(source), cross_(cross) {}

size_t index_submatrix::rows() const { return source_.rows() - 1; }

size_t index_submatrix::columns() const { return source_.columns() - 1; }

pixel index_submatrix::operator[](const pixel &id) const {
  auto subrow = find_subordinal(id.row, cross_.row);
  auto subcolumn = find_subordinal(id.column, cross_.column);
  pixel subid{subcolumn, subrow};
  return source_[subid];
}

size_t index_submatrix::find_subordinal(size_t ordinal, size_t size) {
  return ordinal < size ? ordinal : (ordinal + 1);
}

}  // namespace algebra::matrices