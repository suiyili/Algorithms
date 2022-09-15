#pragma once

#include "generic/parser_factory_i.hpp"

using namespace expression;

namespace expression::parse {

bool has_function(std::string_view expr, view_interval interval);

class parser_factory final : public parser_factory_i {
 public:
  ~parser_factory() override = default;

  parser_ptr create_parser(std::string_view expr, view_interval interval) override;
};

}