#pragma once

#include <stdexcept>

namespace expression {

class parse_error : public std::runtime_error {
 public:
  explicit parse_error(const std::string &message);
  ~parse_error() override = default;
};
}