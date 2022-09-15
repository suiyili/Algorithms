#ifdef TEST

#include "compiler_for_parser_mock.hpp"

compiler_for_parser_mock::compiler_for_parser_mock(size_t &merge_called)
    : merge_called_(merge_called) {}

void compiler_for_parser_mock::merge(std::unique_ptr<compiler_i> other) {
  merge_called_++;
  return;
}

#endif // TEST