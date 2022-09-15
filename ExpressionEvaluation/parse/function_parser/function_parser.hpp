#pragma once

#include "generic/parser_i.hpp"
#include <forward_list>

using namespace expression;

namespace expression::parse {
class function_parser final : public parser_i {
 public:
  function_parser(std::string_view expr, const view_interval& interval);
  ~function_parser() override = default;

  view_interval get_interval() const override;
  void append(parser_ptr child) override;
  std::unique_ptr<compiler_i> create_compiler(compiler_factory_i &factory) override;

 private:
  static std::string_view read_name(std::string_view expr, view_ordinal end) noexcept;
  static view_interval expand_interval(view_interval original, std::string_view name) noexcept;
  std::string_view name_;
  const view_interval interval_;

  std::forward_list<parser_ptr> children_;
  decltype(children_)::const_iterator last_;
};
}