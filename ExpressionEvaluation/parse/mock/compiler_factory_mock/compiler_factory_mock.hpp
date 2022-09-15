#pragma once

#include "generic/compiler_factory_i.hpp"
#include "parse/mock/compiler_for_parser_mock/compiler_for_parser_mock.hpp"

using namespace expression;

class compiler_factory_mock final : public compiler_factory_i {
 public:
  explicit compiler_factory_mock(size_t &merge_called);
  ~compiler_factory_mock() override = default;

  std::unique_ptr <compiler_i> create_top() override;
  std::unique_ptr<compiler_i> create_argument(std::string_view arg) override;
  std::unique_ptr<compiler_i> create_operation(char symbol) override;
  std::unique_ptr<compiler_i> create_function(std::string_view name) override;

  std::vector<std::string_view> get_sections() const;

 private:
  size_t &merge_called_;
  std::string symbols_;
  std::vector<std::string_view> sections_;
};