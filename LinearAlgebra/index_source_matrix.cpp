#include "index_source_matrix.hpp"

namespace algebra::matrices {
index_source_matrix::index_source_matrix(size_t columns, size_t rows)
    : columns_(columns), rows_(rows) {}

size_t index_source_matrix::rows() const { return rows_; }

size_t index_source_matrix::columns() const { return columns_; }

pixel index_source_matrix::operator[](const pixel& id) const { return id; }

}  // namespace algebra::matrices
