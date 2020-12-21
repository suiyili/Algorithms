#pragma once

#include <unordered_map>

namespace expression {

using parameters = std::unordered_map<std::string, double>;

class operand_i {
 public:
  virtual ~operand_i() = default;
  virtual double result_with(const parameters &params) const = 0;
};
}