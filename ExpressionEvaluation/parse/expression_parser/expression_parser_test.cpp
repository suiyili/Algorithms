#ifdef TEST

#include "expression_parser.hpp"
#include "parse/mock/parser_factory_mock/parser_factory_mock.hpp"
#include "parse/mock/parser_mock/parser_mock.hpp"
#include "generic/parse_error/parse_error.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;
namespace expression::parse {

static std::string_view parsed_substr(std::string_view expr,
                                      const parser_i &parser);

SCENARIO("expression construct test", "[expression_parser]") {

  parser_factory_mock factory;
  GIVEN("an empty expression") {
    std::string_view expr;
    WHEN("create expression parser") {

      THEN("it should throw exception") {

        auto ctor = [](std::string_view &expr) {
          expression_parser parser(expr);
        };
        REQUIRE_THROWS_AS(ctor(expr), std::invalid_argument);
      }
    }
  }

  GIVEN("expression with more open parentheses") {
    std::string_view expr("a+((b-c)+d"sv);
    WHEN("create expression parser") {
      THEN("it should throw parse error") {
        auto ctor = [](std::string_view &expr) {
          expression_parser parser(expr);
        };
        REQUIRE_THROWS_AS(ctor(expr), parse_error);
      }
    }
  }

  GIVEN("expression with more close parentheses") {
    std::string_view expr("((a-b)*3+(b+5)))-2"sv);
    WHEN("create expression parser") {
      THEN("it should throw parse error") {
        auto ctor = [](std::string_view &expr) {
          expression_parser parser(expr);
        };
        REQUIRE_THROWS_AS(ctor(expr), parse_error);
      }
    }
  }

  GIVEN("expression with reversed parentheses") {
    std::string_view expr("a)+(b"sv);
    WHEN("create parsers") {
      THEN("it should throw parse error") {
        auto ctor = [](std::string_view &expr) {
          expression_parser parser(expr);
        };
        REQUIRE_THROWS_AS(ctor(expr), parse_error);
      }
    }
  }

  GIVEN("expression with half open parentheses") {
    std::string_view expr("a+sin(b,c"sv);
    WHEN("create parsers") {
      THEN("it should throw parse error") {
        auto ctor = [](std::string_view &expr) {
          expression_parser parser(expr);
        };
        REQUIRE_THROWS_AS(ctor(expr), parse_error);
      }
    }
  }

  GIVEN("expression with many level of parentheses") {
    std::string_view expr("(((a)+pow((b-w),cos(c+c))+2))"sv);
    WHEN("create parsers") {
      THEN("it should be OK") {
        auto ctor = [](std::string_view &expr) {
          expression_parser parser(expr);
        };
        REQUIRE_NOTHROW(ctor(expr));
      }
    }
  }
}

SCENARIO("parsing parentheses and comma test", "[expression_parser]") {

  parser_factory_mock factory;

  GIVEN("an expressions without parentheses") {

    std::string_view expr("a+3-5*4/8"sv);

    WHEN("it creates parser object") {

      expression_parser parser(expr);
      auto top = parser.create(factory);
      auto mock_top = dynamic_cast<parser_mock *>(top.get());
      CHECK(mock_top);

      THEN("it should have no child") { REQUIRE(mock_top->children().empty()); }
      AND_THEN("its interval contains whole expression") {
        REQUIRE(parsed_substr(expr, *mock_top) == expr);
      }
    }
  }

  GIVEN("a complex expression with multi-level parentheses") {

    std::string_view expr("a-3+((8-5)*3)*(b-2)/1"sv);

    WHEN("it creates parser objects") {
      expression_parser parser(expr);
      auto top = parser.create(factory);
      auto mock_top = dynamic_cast<parser_mock *>(top.get());
      CHECK(mock_top);

      THEN("its interval includes the whole expression") {
        REQUIRE(parsed_substr(expr, *mock_top) == expr);
      }
      AND_THEN(
          "it should remove outer most parentheses and so have two child") {
        REQUIRE(mock_top->children().size() == 2U);
      }
      AND_THEN("its children intervals are those insider parentheses") {
        auto child =
            dynamic_cast<parser_mock *>(mock_top->children().front().get());
        REQUIRE(parsed_substr(expr, *child) == "((8-5)*3)"sv);
        child = dynamic_cast<parser_mock *>(mock_top->children().back().get());
        REQUIRE(parsed_substr(expr, *child) == "(b-2)"sv);
      }
      AND_THEN("its first grand child has one child") {
        auto child =
            dynamic_cast<parser_mock *>(mock_top->children().front().get());
        REQUIRE(child->children().size() == 1U);
        auto grand_child =
            dynamic_cast<parser_mock *>(child->children().front().get());
        REQUIRE(parsed_substr(expr, *grand_child) == "(8-5)"sv);
      }
    }
  }

  GIVEN("a simple function expression") {
    std::string_view expr("cos(a-3)"sv);

    WHEN("it creates parser objects") {
      expression_parser parser(expr);
      auto top = parser.create(factory);
      auto mock_top = dynamic_cast<parser_mock *>(top.get());
      CHECK(mock_top);

      THEN("its top interval includes the whole expression") {
        REQUIRE(parsed_substr(expr, *mock_top) == expr);
      }
      AND_THEN(
          "it should remove outer most parentheses and so have two child") {
        REQUIRE(mock_top->children().size() == 1U);
      }
      AND_THEN("its children intervals are those insider parentheses") {
        auto child =
            dynamic_cast<parser_mock *>(mock_top->children().front().get());
        REQUIRE(parsed_substr(expr, *child) == "(a-3)"sv);
      }
      AND_THEN("it has one grand child") {
        auto child =
            dynamic_cast<parser_mock *>(mock_top->children().front().get());
        REQUIRE(child->children().size() == 1U);
        auto first_grand_child =
            dynamic_cast<parser_mock *>(child->children().front().get());
        REQUIRE(parsed_substr(expr, *first_grand_child) == "a-3"sv);
      }
    }
  }

  GIVEN("a recursive function expression") {

    std::string_view expr("pow(max(a-3,1),5-2)"sv);

    WHEN("it creates parser objects") {
      expression_parser parser(expr);
      auto top = parser.create(factory);
      auto mock_top = dynamic_cast<parser_mock *>(top.get());
      CHECK(mock_top);

      THEN("its children intervals are those insider parentheses") {
        auto child =
            dynamic_cast<parser_mock *>(mock_top->children().front().get());
        REQUIRE(parsed_substr(expr, *child) == "(max(a-3,1),5-2)"sv);
      }
      AND_THEN("it has two grand children around comma") {
        auto child =
            dynamic_cast<parser_mock *>(mock_top->children().front().get());
        REQUIRE(child->children().size() == 2U);
        auto first_grand_child =
            dynamic_cast<parser_mock *>(child->children().front().get());
        REQUIRE(parsed_substr(expr, *first_grand_child) == "max(a-3,1)"sv);
        auto great_grand_child = dynamic_cast<parser_mock *>(
            first_grand_child->children().front().get());
        REQUIRE(great_grand_child->children().size() == 2U);
        REQUIRE(parsed_substr(expr, *great_grand_child) == "(a-3,1)"sv);
        auto second_grand_child =
            dynamic_cast<parser_mock *>(child->children().back().get());
        REQUIRE(parsed_substr(expr, *second_grand_child) == "5-2"sv);
      }
    }
  }
}

std::string_view parsed_substr(std::string_view expr, const parser_i &parser) {
  auto interval = parser.get_interval();
  return expr.substr(interval.first, interval.second - interval.first);
}

} // namespace expression::parse

#endif // TEST