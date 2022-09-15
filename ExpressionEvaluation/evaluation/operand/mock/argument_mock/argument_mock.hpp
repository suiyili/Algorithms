#pragma once

#include "generic/operand_i.hpp"

using namespace expression;

class argument_mock final : public operand_i {
 public:
  explicit argument_mock(std::string_view arg);
  ~argument_mock() override = default;

  double result_with(const parameters &params) const override;

 private:
  const std::string arg_;
};