#pragma once

#include "generic/compiler_i.hpp"

using namespace expression;

class argument_compiler_mock final : public compiler_i {
 public:
  explicit argument_compiler_mock(std::string_view arg);
  ~argument_compiler_mock() override = default;

  std::unique_ptr<operand_i> compile() const override;
  arithmetic_priority get_priority() const override;
  void merge(std::unique_ptr<compiler_i>) override;

 private:
  std::string_view arg_;
};
