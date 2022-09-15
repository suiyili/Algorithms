#pragma once

#include "generic/parser_i.hpp"
#include "generic/parser_factory_i.hpp"
#include "compile/compile_utility/compile_utility.hpp"
#include <forward_list>
#include <array>

using namespace expression::compile;

namespace expression::parse {

class operator_parser final : public parser_i {
 public:
  operator_parser(std::string_view expr, const view_interval& interval);
  ~operator_parser() override = default;

  view_interval get_interval() const override;
  void append(parser_ptr child) override;
  std::unique_ptr<compiler_i> create_compiler(compiler_factory_i &factory) override;

 private:
  static bool is_negative(char ch) noexcept;
  view_interval get_slot_interval() const noexcept;
  static std::forward_list<std::unique_ptr<compiler_i>> make_children(std::string_view expr, compiler_factory_i &factory);
  static void add_children(compiler_i &top, std::forward_list<std::unique_ptr<compiler_i>> children);

  static std::string_view substr(std::string_view expr, const view_interval& interval) noexcept;
  static bool is_valid(const view_interval& interval) noexcept;

  bool is_inside() const noexcept;

  static constexpr std::array<char, 5> operators_ = {add_operator,
                                                subtract_operator,
                                                multiply_operator,
                                                divide_operator,
                                                exponentiate_operator};

  std::string_view expr_;
  const view_interval interval_;
  std::forward_list<parser_ptr> children_;
  decltype(children_)::const_iterator last_;
};

}