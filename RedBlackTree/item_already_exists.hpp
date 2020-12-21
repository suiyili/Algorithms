#pragma once

#include <stdexcept>

namespace bbtree {
class item_already_exists : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

} // namespace bbtree
