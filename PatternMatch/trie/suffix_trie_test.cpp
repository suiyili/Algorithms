#ifdef TEST

#include "suffix_trie.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;

namespace pattern_match::trie{
  //todo 
  //test 1. suffix search
  //test 2. suffix count
  //test 3. common longest match
  //test 4. return longest repeat.
  SCENARIO("suffix trie test", "[suffix_trie]") {

    GIVEN("a pattern")
    {
      std::string_view pattern = "xabcdababcda"sv;
      suffix_trie trie(pattern);
      AND_GIVEN("a good target"){
        auto target = "cda"sv;
        WHEN("check if the parttern contains target"){
          auto found = trie.contains(target);
          THEN("it should contain the target"){
            REQUIRE(found);
          }        
        }
        WHEN("find the target from pattern"){
          auto found = trie.find(target);
          THEN("it should return the first occur position"){
            REQUIRE(found == 3U);
          }
        }        
      }
      AND_GIVEN("an bad target"){
        auto target = "aabx"sv;
        WHEN("check if the parttern contains target")
        {
          auto found = trie.contains(target);
          THEN("it should not contain the target")
          {
            REQUIRE_FALSE(found);
          }
        }
        WHEN("find the target from pattern")
        {
          auto found = trie.find(target);
          THEN("it should return the length of pattern")
          {
            REQUIRE(found == pattern.size());
          }
        }
      }
      AND_GIVEN("a repeative target"){
        auto target = "ab"sv;
        WHEN("count the target in pattern"){
          auto occurs = trie.counts(target);
          THEN("it will count the number of occurs"){
            REQUIRE(occurs == 2U);
          }
        }
      }
      AND_GIVEN("a sub matched target"){
        auto target = "yabcdabax"sv;
        WHEN("find the longest match in pattern"){
          auto info = trie.find_longest_match(target);
          THEN("it should return the first longest match in target"){
            REQUIRE(info.first == 1U);
            REQUIRE(info.second == 7U);
          }
        }
      }
      WHEN("get longest repeat"){
        THEN("it should return the first occurrs info"){
          auto info = trie.get_longest_repeat();
          REQUIRE(info.first == 1U);
          REQUIRE(info.second == 5U);
        }
      }
    }
  
  }
}

#endif