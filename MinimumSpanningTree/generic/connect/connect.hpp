#pragma once

#include <cstddef>

namespace tree::generic {
class connect {
 public:
  connect(std::size_t from, std::size_t to);
  std::size_t from() const;
  std::size_t to() const;
  friend bool operator == (const connect& lh, const connect& rh);

 private:
  const std::size_t from_, to_;
};

bool operator == (const connect& lh, const connect& rh);

}  // namespace tree::generic
