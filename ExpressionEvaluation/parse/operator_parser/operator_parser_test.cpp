#ifdef TEST

#include "operator_parser.hpp"
#include "parse/mock/compiler_factory_mock/compiler_factory_mock.hpp"
#include "parse/mock/compiler_for_parser_mock/compiler_for_parser_mock.hpp"
#include "parse/mock/parser_mock/parser_mock.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using namespace Catch::Matchers;
using namespace std::string_view_literals;
namespace expression::parse {

class operator_parser_test final {
public:
  explicit operator_parser_test(std::string_view expr);
  void add_child(parser_ptr child);
  const std::vector<std::string_view> parse_to_sections();

private:
  std::string_view expr_;
  size_t merge_called_ = 0;
  compiler_factory_mock factory_;
  std::vector<parser_ptr> children_;
};

SCENARIO("operator parser plain expression test", "[operator_parser]") {

  GIVEN("an expression without parentheses or child parser") {
    operator_parser_test tester("3.2+1.23+4"sv);

    WHEN("create compiler") {
      const auto &&sections_actual = tester.parse_to_sections();
      THEN("it should call compiler factory with operator separated sections") {
        const std::vector<std::string_view> sections_expected{
            "top"sv, "3.2"sv, "+"sv, "1.23"sv, "+"sv, "4"sv};
        REQUIRE_THAT(sections_actual, Equals(sections_expected));
      }
    }
  }

  GIVEN("an expression with parentheses") {
    operator_parser_test tester("(3.2*4)"sv);

    WHEN("create compiler") {
      const auto &&sections_actual = tester.parse_to_sections();
      THEN("it should call parser factory with sections including parentheses "
           "part") {
        const std::vector<std::string_view> sections_expected{"top", "3.2", "*",
                                                              "4"};
        REQUIRE_THAT(sections_actual, Equals(sections_expected));
      }
    }
  }

  GIVEN("an expression with minus in the front") {
    operator_parser_test tester("(-3.2+1.23)"sv);

    WHEN("create compiler without parenthesis") {
      const auto &&sections_actual = tester.parse_to_sections();
      THEN("it should call compiler factory with extra zero argument in "
           "sections") {
        const std::vector<std::string_view> sections_expected{
            "top", "0", "-", "3.2", "+", "1.23"};
        REQUIRE_THAT(sections_actual, Equals(sections_expected));
      }
    }
  }
}

SCENARIO("operator parser recursive expression test", "[operator_parser]") {

  GIVEN("an expression with multi parentheses all in same level") {
    operator_parser_test tester("(a-b)*(-3.2+1.23)"sv);
    constexpr std::string_view mock_expr("$");
    tester.add_child(std::make_unique<parser_mock>(
        mock_expr, std::make_pair(0U, 5U))); //(a-b)
    tester.add_child(std::make_unique<parser_mock>(
        mock_expr, std::make_pair(6U, 17U))); //(-3.2+1.23)

    WHEN("create compiler without parenthesis") {
      const auto &&sections_actual = tester.parse_to_sections();
      THEN("it should call compiler factory with top added sections") {
        const std::vector<std::string_view> sections_expected{"top", "$", "*",
                                                              "$"};
        REQUIRE_THAT(sections_actual, Equals(sections_expected));
      }
    }
  }

  GIVEN("an expression with sub expression") {
    operator_parser_test tester("(3.2*(4-a)+5-sin(2,b))"sv);
    constexpr std::string_view mock_expr("$");

    tester.add_child(std::make_unique<parser_mock>(
        mock_expr, std::make_pair(5U, 10U))); //(4-a)
    tester.add_child(std::make_unique<parser_mock>(
        mock_expr, std::make_pair(13U, 21U))); // sin(2,b)

    WHEN("create compiler") {
      const auto &&sections_actual = tester.parse_to_sections();
      THEN("it should peel the out-most parenthesis and create compiler for "
           "internal sections") {
        const std::vector<std::string_view> sections_expected{
            "top", "3.2", "*", "$", "+", "5", "-", "$"};
        REQUIRE_THAT(sections_actual, Equals(sections_expected));
      }
    }
  }
}

operator_parser_test::operator_parser_test(std::string_view expr)
    : expr_(expr), factory_(merge_called_) {}

const std::vector<std::string_view> operator_parser_test::parse_to_sections() {
  operator_parser parser(expr_, std::make_pair(0U, expr_.size()));
  for (auto &child : children_)
    parser.append(move(child));
  parser.create_compiler(factory_);
  return factory_.get_sections();
}

void operator_parser_test::add_child(parser_ptr child) {
  children_.push_back(move(child));
}

} // namespace expression::parse

#endif // TEST