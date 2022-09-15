#pragma once

#include "generic/compiler_i.hpp"
#include <stdexcept>

using namespace expression;

class compiler_for_parser_mock final : public compiler_i {
 public:
  explicit compiler_for_parser_mock(size_t &merge_called);
  ~compiler_for_parser_mock() override = default;
  arithmetic_priority get_priority() const override { throw std::logic_error("not supported"); }
  void merge(std::unique_ptr<compiler_i> other) override;
  std::unique_ptr<operand_i> compile() const override { throw std::logic_error("not supported"); };

 private:
  size_t &merge_called_;
};