#pragma once

#include <stdexcept>

namespace bbtree {
class color_error : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

} // namespace bbtree
