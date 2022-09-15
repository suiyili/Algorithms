#pragma once

#include "generic/expression_types.hpp"
#include "parser_i.hpp"

namespace expression {
class parser_factory_i {
 public:
  virtual~parser_factory_i() = default;
  virtual parser_ptr create_parser(std::string_view expr, view_interval interval) = 0;
};
}