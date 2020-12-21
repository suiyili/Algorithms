#ifdef TEST

#include "parser_mock.hpp"

parser_mock::parser_mock(std::string_view expr, view_interval interval)
    : expr_(expr), interval_(move(interval)), children_(0U) {}

std::unique_ptr<compiler_i> parser_mock::create_compiler(compiler_factory_i &factory) {
  return factory.create_argument(expr_);
}

view_interval parser_mock::get_interval() const {
  return interval_;
}

void parser_mock::append(parser_ptr child) {
  children_.push_back(move(child));
}

std::vector<parser_ptr> &parser_mock::children() {
  return children_;
}

#endif // TEST