#pragma once

#include <stdexcept>

namespace btree::generic {

class color_error : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

class rotate_error : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

class item_not_exists : public std::domain_error {
public:
  using std::domain_error::domain_error;
  virtual ~item_not_exists() override = default;
};

class item_already_exists : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

} // namespace btree::generic