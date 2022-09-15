#ifdef TEST

#include "parser_factory_mock.hpp"
#include "parse/mock/parser_mock/parser_mock.hpp"

parser_ptr parser_factory_mock::create_parser(std::string_view expr, view_interval interval) {
  return std::make_unique<parser_mock>(expr, move(interval));
}

#endif // TEST