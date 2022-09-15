#pragma once

#include "generic/parser_factory_i.hpp"
#include "parse/parse_utility.hpp"
#include <forward_list>
#include <array>
#include <list>

namespace expression::parse {
class expression_parser final {
 public:
  explicit expression_parser(std::string_view expr);
  parser_ptr create(parser_factory_i &factory);
 
private:
  enum class priority : char {
    open = -1,
    semi_close = 0,
    close = 1
  };

  class interval_node {
   public:
    explicit interval_node(std::string_view expr, view_ordinal start, bool is_inside = false) noexcept;
    interval_node(interval_node &&other) noexcept;
    void close(view_ordinal end_pos) noexcept;
    bool is_inside()const noexcept;
    void append(interval_node child);
    parser_ptr create(parser_factory_i &factory) const;

   private:
    std::string_view expr_;
    view_interval interval_;
    const bool is_inside_;
    std::list<interval_node> children_;
  };
  using node_stack = std::forward_list<interval_node>;

  static std::string_view check_expression(std::string_view expr);
  static bool is_function(std::string_view expr, view_ordinal start) noexcept;
  static priority get_priority(std::string_view expr, view_ordinal ordinal) noexcept;
  static void close_last_child(node_stack &stack, view_ordinal close_end);
  static interval_node build_topological_expression(std::string_view expr);

  static constexpr std::array<char, 3U> delimiters_ = {
      to_char(interval_state::open),
      to_char(interval_state::semi_close),
      to_char(interval_state::close)};

  static const std::unordered_map<char, priority> priority_table_;

  interval_node top_;
};
}
