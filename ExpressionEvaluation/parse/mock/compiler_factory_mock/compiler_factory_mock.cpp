#ifdef TEST

#include "compiler_factory_mock.hpp"
#include "parse/mock/compiler_for_parser_mock/compiler_for_parser_mock.hpp"

compiler_factory_mock::compiler_factory_mock(size_t &merge_called)
    : merge_called_(merge_called) {
  symbols_.reserve(1000U);
}

std::vector<std::string_view> compiler_factory_mock::get_sections() const {
  std::vector<std::string_view> sections(sections_);
  return sections;
}

std::unique_ptr<compiler_i> compiler_factory_mock::create_top() {
  sections_.emplace_back("top");
  return std::make_unique<compiler_for_parser_mock>(merge_called_);
}

std::unique_ptr<compiler_i> compiler_factory_mock::create_argument(std::string_view arg) {
  sections_.emplace_back(arg);
  return std::make_unique<compiler_for_parser_mock>(merge_called_);
}

std::unique_ptr<compiler_i> compiler_factory_mock::create_operation(char symbol) {
  auto last = symbols_.data() + symbols_.size();
  symbols_.push_back(symbol);
  sections_.emplace_back(std::string_view(last, 1U));
  return std::make_unique<compiler_for_parser_mock>(merge_called_);
}

std::unique_ptr<compiler_i> compiler_factory_mock::create_function(std::string_view name) {
  sections_.emplace_back(name);
  return std::make_unique<compiler_for_parser_mock>(merge_called_);
}

#endif // TEST