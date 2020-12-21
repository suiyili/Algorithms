#include "bit_analyzer.hpp"

namespace algebra::generic {

bit_analyzer::bit_analyzer(size_t value)
    : value_(value) {
  move_start();
}

void bit_analyzer::move_start() {
  cursor_ = value_.size();
  next_ = 0;
}

size_t bit_analyzer::move_next_true() {
  for (; next_ < value_.size() && !value_.test(next_); ++next_);

  auto span = value_.size();

  if (next_ < value_.size()) {
    span = next_ - cursor_ % value_.size();
    cursor_ = next_;
    next_ = cursor_ + 1;
  }

  return span;
}

size_t bit_analyzer::no_next_true() const {
  return value_.size();
}

}