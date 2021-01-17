#include "connect.hpp"

#include <algorithm>

namespace tree::generic {
connect::connect(std::size_t from, std::size_t to)
    : from_(std::max(from, to)), to_(std::min(from, to)) {}
std::size_t connect::from() const { return from_; }
std::size_t connect::to() const { return to_; }

bool operator==(const connect& lh, const connect& rh) {
  return lh.from_ == rh.from_ && lh.to_ == rh.to_;
}
}  // namespace tree::generic
