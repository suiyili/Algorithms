#pragma once

#include <stdexcept>

namespace bbtree {
class item_not_exists : public std::domain_error {
public:
  using std::domain_error::domain_error;
  virtual ~item_not_exists() override = default;
};
} // namespace bbtree