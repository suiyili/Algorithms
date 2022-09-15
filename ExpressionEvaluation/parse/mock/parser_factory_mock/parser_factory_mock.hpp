#pragma once

#include "generic/parser_factory_i.hpp"

using namespace expression;

class parser_factory_mock final : public parser_factory_i {
 public:
  parser_ptr create_parser(std::string_view expr, view_interval interval) override;
};