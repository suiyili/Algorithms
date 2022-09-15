#pragma once

#include "generic/compiler_i.hpp"
using namespace expression;

class compiler_mock final : public compiler_i {
 public:
  explicit compiler_mock(size_t id = 0U);
  ~compiler_mock() override = default;

  arithmetic_priority get_priority() const override;
  void merge(std::unique_ptr<compiler_i> compiler) override;
  std::unique_ptr<operand_i> compile() const override;

  void set_priority(arithmetic_priority priority);
  bool merge_called() const;
  size_t id() const;
  size_t get_mock_id_if_merged() const;

 private:
  const size_t id_;
  arithmetic_priority priority_ = arithmetic_priority::level_zero;
  bool merged_ = false;
  size_t merged_id_;
};