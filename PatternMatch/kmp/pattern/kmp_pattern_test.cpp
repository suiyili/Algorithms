#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include "kmp_pattern.hpp"

using namespace std::string_view_literals;

namespace pattern_match::kmp {
SCENARIO("kmp pattern test", "kmp_pattern") {
  GIVEN("a pattern string") {
    auto str = "ababaca"sv;
    kmp_pattern pattern(str);
    WHEN("get value from position") {
      THEN("it should get the char") {
        REQUIRE(str[0] == pattern[0]);
        REQUIRE(str[3] == pattern[3]);
        REQUIRE(str[str.size() - 1] == pattern[pattern.size() - 1]);
      }
    }
    WHEN("get prefix") {
      THEN("it should follow kmp prefix") {
        REQUIRE(pattern.prefix(0) == 0);
        REQUIRE(pattern.prefix(1) == 0);
        REQUIRE(pattern.prefix(2) == 0);
        REQUIRE(pattern.prefix(3) == 1);
        REQUIRE(pattern.prefix(4) == 2);
        REQUIRE(pattern.prefix(5) == 3);
        REQUIRE(pattern.prefix(6) == 0);
        REQUIRE(pattern.prefix(7) == 1);
      }
    }
    WHEN("get size") {
      THEN("it should be same as the input string") {
        REQUIRE(str.size() == pattern.size());
      }
    }
  }
}
} // namespace pattern_match::kmp

#endif // TEST
