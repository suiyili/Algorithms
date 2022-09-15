#ifdef TEST

#include "compiler_mock.hpp"
#include <stdexcept>

compiler_mock::compiler_mock(size_t id): id_(id), merged_id_(id){}

std::unique_ptr<operand_i> compiler_mock::compile() const {
  throw std::logic_error("not supported");
}

void compiler_mock::merge(std::unique_ptr<compiler_i> compiler) {
 merged_ = true;
 auto mock = dynamic_cast<decltype(this)>(compiler.get());
 if(mock)
   merged_id_ = mock->id();
}

arithmetic_priority compiler_mock::get_priority() const {
  return priority_;
}

size_t compiler_mock::id() const {
  return id_;
}

void compiler_mock::set_priority(arithmetic_priority priority) {
  priority_ = priority;
}

bool compiler_mock::merge_called() const {
  return merged_;
}
size_t compiler_mock::get_mock_id_if_merged() const {
  return merged_id_;
}

#endif // TEST