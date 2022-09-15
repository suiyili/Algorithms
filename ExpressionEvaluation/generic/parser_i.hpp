#pragma once

#include "generic/expression_types.hpp"
#include "compiler_factory_i.hpp"

namespace expression {
class parser_i;
using parser_ptr = std::unique_ptr<parser_i>;

class parser_i {
 public:
  virtual~parser_i() = default;
  virtual view_interval get_interval() const = 0;
  virtual void append(parser_ptr child) = 0;
  virtual std::unique_ptr<compiler_i> create_compiler(compiler_factory_i &factory) = 0;
};
}