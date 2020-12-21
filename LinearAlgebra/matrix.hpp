#pragma once

#include "matrix.h"
#include <stdexcept>

namespace algebra::matrices {

template <typename T>
inline matrix<T>::matrix(size_t columns, size_t rows)
    : rows_(rows), columns_(columns), data_(zero<T>, rows * columns) {
  if (columns_ == 0U || rows_ == 0U) throw std::invalid_argument("invalid column or row");
}

template <typename T>
inline matrix<T>::matrix(size_t size) : matrix<T>(size, size) {}

template <typename T>
inline matrix<T>::matrix(std::initializer_list<std::initializer_list<T>> data)
    : rows_(get_row_count(data)),
      columns_(get_columns_count(data)),
      data_(rows_ * columns_) {
  size_t row_cursor = 0;
  for (auto &row : data) {
    size_t col_cursor = 0;
    for (auto &col : row) {
      data_[row_cursor * columns_ + col_cursor] = col;
      ++col_cursor;
    }
    ++row_cursor;
  }
}

template <typename T>
inline matrix<T>::matrix(const matrix &other)
    : rows_(other.rows_), columns_(other.columns_), data_(other.data_) {}

template <typename T>
matrix<T>::matrix(matrix &&other) noexcept
    : rows_(other.rows_), columns_(other.columns_), data_(move(other.data_)) {}

template <typename T>
inline matrix<T> &matrix<T>::operator=(const matrix<T> &other) {
  if (this != &other) {
    if (other.columns_ != columns_ || other.rows_ != rows_)
      throw std::invalid_argument("assign failed");
    data_ = other.data_;
  }
  return *this;
}

template <typename T>
inline matrix<T> &matrix<T>::operator=(matrix<T> &&other) {
  if (this != &other) {
    if (other.columns_ != columns_ || other.rows_ != rows_)
      throw std::invalid_argument("assign failed");
    data_ = std::move(other.data_);
  }  
  return *this;
}

template <typename T>
size_t matrix<T>::rows() const noexcept{
  return rows_;
}

template <typename T>
size_t matrix<T>::columns() const noexcept {
  return columns_;
}

template <typename T>
const T &matrix<T>::operator[](const pixel &id) const {
  if (id.column < columns_ && id.row < rows_)
    return data_[id.row * columns_ + id.column];
  throw std::out_of_range("out of range");
}

template <typename T>
T &matrix<T>::operator[](const pixel &id) {
  if (id.column < columns_ && id.row < rows_)
    return data_[id.row * columns_ + id.column];
  throw std::out_of_range("out of range");
}

template <typename T>
algebra_vector<T> matrix<T>::row(size_t ordinal) const {
  if (ordinal < rows_)
    return data_[std::slice(ordinal * columns_, columns_, 1)];
  throw std::out_of_range("out of range");
}

template <typename T>
algebra_vector<T> matrix<T>::column(size_t ordinal) const {
  if (ordinal < columns_) 
	return data_[std::slice(ordinal, rows_, columns_)];
  throw std::out_of_range("out of range");
}

template <typename T>
size_t matrix<T>::get_row_count(
    const std::initializer_list<std::initializer_list<T>> &data) {
  auto rows = data.size();
  if (rows == 0) throw std::invalid_argument("row must be greater than 0");
  return rows;
}

template <typename T>
size_t matrix<T>::get_columns_count(
    const std::initializer_list<std::initializer_list<T>> &data) {
  auto cols = data.begin()->size();
  if (cols == 0) throw std::invalid_argument("column must be greater than 0");

  if (!all_of(data.begin(), data.end(),
              [&cols](const std::initializer_list<T> &col) {
                return col.size() == cols;
              }))
    throw std::invalid_argument("all columns must be equal");
  return cols;
}

}  // namespace algebra::matrices