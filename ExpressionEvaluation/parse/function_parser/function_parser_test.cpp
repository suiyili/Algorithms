#ifdef TEST

#include "function_parser.hpp"
#include "parse/mock/compiler_factory_mock/compiler_factory_mock.hpp"
#include "parse/mock/parser_mock/parser_mock.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using namespace std::string_view_literals;
using namespace Catch::Matchers;

namespace expression::parse {

class function_parser_test final {
public:
  explicit function_parser_test(std::string_view expr);
  void add_child(parser_ptr child);
  const std::vector<std::string_view>
  parse_to_sections(const view_interval &interval);

private:
  std::string_view expr_;
  size_t merge_called_ = 0;
  compiler_factory_mock factory_;
  std::vector<parser_ptr> children_;
};

SCENARIO("function parser test", "[function_parser]") {

  GIVEN("a function parser start from left parenthesis") {
    function_parser parser("func(1.23-4,a*3)"sv, std::make_pair(4U, 16U));
    WHEN("get interval") {
      auto interval = parser.get_interval();
      THEN("it should expand the interval to include func name") {
        REQUIRE(interval == view_interval(0U, 16U));
      }
    }
  }
  GIVEN("a function with expression as its parameters") {
    function_parser_test tester("3.2+func(1.23-4,a*3)*4"sv);
    constexpr std::string_view mock_expr("$");
    tester.add_child(std::make_unique<parser_mock>(
        mock_expr, std::make_pair(11U, 15U))); // 1.23-4
    tester.add_child(std::make_unique<parser_mock>(
        mock_expr, std::make_pair(16U, 19U))); // a*3

    WHEN("create compiler") {
      const auto &&sections_actual =
          tester.parse_to_sections(std::make_pair(8U, 16U)); //(1.23-4..)
      THEN("it should call parser factory with sections including function "
           "part") {
        const std::vector<std::string_view> sections_expected{"func", "$", "$"};
        REQUIRE_THAT(sections_actual, Equals(sections_expected));
      }
    }
  }
}

function_parser_test::function_parser_test(std::string_view expr)
    : expr_(expr), factory_(merge_called_) {}

const std::vector<std::string_view>
function_parser_test::parse_to_sections(const view_interval &interval) {
  function_parser parser(expr_, interval);
  for (auto &child : children_)
    parser.append(move(child));
  parser.create_compiler(factory_);
  return factory_.get_sections();
}

void function_parser_test::add_child(parser_ptr child) {
  children_.push_back(move(child));
}

} // namespace expression::parse

#endif // TEST