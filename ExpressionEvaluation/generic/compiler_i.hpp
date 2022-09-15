#pragma once

#include "operand_i.hpp"
#include <memory>
#include <vector>

namespace expression {

enum class arithmetic_priority : unsigned char {
  level_three = 3,
  level_two = 2,
  level_one = 1,
  level_zero = 0
};

class compiler_i {
 public:
  virtual ~compiler_i() = default;
  virtual arithmetic_priority get_priority() const = 0;
  virtual void merge(std::unique_ptr<compiler_i> compiler) = 0;
  virtual std::unique_ptr<operand_i> compile() const = 0;
};

using argument_compilers = std::vector<std::unique_ptr<compiler_i>>;
}