#pragma once

#include "generic/operand_i.hpp"

namespace expression::evaluate {

class argument final : public operand_i {
 public:
  explicit argument(const std::string_view &arg);
  ~argument() override = default;

  double result_with(const parameters &params) const override;

 private:
  const std::string_view arg_;
};

}