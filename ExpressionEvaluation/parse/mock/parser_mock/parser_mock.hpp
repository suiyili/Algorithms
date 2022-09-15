#pragma once

#include "generic/parser_i.hpp"

using namespace expression;

class parser_mock final : public parser_i {
 public:
  parser_mock(std::string_view expr, view_interval interval);
  ~parser_mock() override = default;

  view_interval get_interval() const override;
  void append(parser_ptr child) override;
  std::unique_ptr<compiler_i> create_compiler(compiler_factory_i &factory) override;

  std::vector<parser_ptr> &children();

 private:
  std::string_view expr_;
  const view_interval interval_;
  std::vector<parser_ptr> children_;
};