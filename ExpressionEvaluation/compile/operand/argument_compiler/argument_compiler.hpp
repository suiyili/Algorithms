#pragma once

#include "generic/compiler_i.hpp"

using namespace expression;

namespace expression::compile {

class argument_compiler final : public compiler_i {
 public:
  explicit argument_compiler(std::string_view arg);
  ~argument_compiler() override = default;

  arithmetic_priority get_priority() const override;
  void merge(std::unique_ptr<compiler_i> compiler) override;
  std::unique_ptr<operand_i> compile() const override;

 private:
  std::string_view arg_;
};

}