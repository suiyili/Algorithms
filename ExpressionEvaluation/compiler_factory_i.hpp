#pragma once

#include "compiler_i.hpp"

namespace expression {

class compiler_factory_i {
 public:
  virtual ~compiler_factory_i() = default;
  virtual std::unique_ptr<compiler_i> create_top() = 0;
  virtual std::unique_ptr<compiler_i> create_argument(std::string_view arg) = 0;
  virtual std::unique_ptr<compiler_i> create_operation(char symbol) = 0;
  virtual std::unique_ptr<compiler_i> create_function(std::string_view name) = 0;
};
}  // namespace expression