#pragma once

#include "generic/expression_types.hpp"
#include "generic/compiler_factory_i.hpp"
#include "generic/operand_i.hpp"

namespace expression::compile {

class compiler_factory : public compiler_factory_i {
 public:
  compiler_factory();
  ~compiler_factory() override = default;

  void prepare(const std::string_view &function_name, const evaluation_function& user_function);

  std::unique_ptr<compiler_i> create_top() override;
  std::unique_ptr<compiler_i> create_argument(std::string_view arg) override;
  std::unique_ptr<compiler_i> create_operation(char arithmetic_operator) override;
  std::unique_ptr<compiler_i> create_function(std::string_view name) override;

 private:
  std::unordered_map<std::string_view, evaluation_function> function_mapping_;
};

}