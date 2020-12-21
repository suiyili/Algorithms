#ifdef TEST

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "kmp_search.hpp"

using namespace std::string_view_literals;

namespace pattern_match::kmp {
SCENARIO("kmp test", "[kmp]") {
  GIVEN("a target string") {
    auto target = "ababcdabca"sv;
    AND_GIVEN("a pattern which is not in it") {
      kmp_pattern pattern ("abcs"sv);
      WHEN("search for the pattern") {
        auto pos = kmp_search(target, pattern);
        THEN("it should return -1") { REQUIRE(pos == target.size()); }
      }
    }
    AND_GIVEN("a pattern which is in the target") {
      kmp_pattern pattern("abc"sv);
      WHEN("search for the pattern") {
        auto pos = kmp_search(target, pattern);
        THEN("it should return the first occurred position") {
          REQUIRE(pos == 2);
        }
      }
    }
  }
}
} // namespace pattern_match::kmp
#endif // TEST
