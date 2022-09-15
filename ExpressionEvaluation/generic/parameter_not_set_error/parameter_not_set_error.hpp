#pragma once

#include <stdexcept>

namespace expression {
class parameter_not_set_error final : public std::logic_error {
 public:
  explicit parameter_not_set_error(const std::string &what_arg);
  explicit parameter_not_set_error(const char *what_arg);
  ~parameter_not_set_error() = default;

};

}