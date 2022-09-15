#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include "bit_tree.hpp" 

namespace tree {
  SCENARIO("bit tree test", "[bit_tree_algo]") {
    GIVEN("a bit tree"){
      bit_tree<char> tree;
      WHEN("add new values") {
        int i = 1, j = -3, z = 0;
        auto i_v = std::make_unique<char>('i');
        auto j_v = std::make_unique<char>('j');
        auto z_v = std::make_unique<char>('z');

        auto set_positive = tree.add(i, i_v.get());
        auto set_negative = tree.add(j, j_v.get());
        auto set_neutral = tree.add(z, z_v.get());
        THEN("it should indicate if the value is added") {
          REQUIRE(set_positive);
          REQUIRE(tree.get(i) == i_v.get());
          REQUIRE(set_negative);
          REQUIRE(tree.get(j) == j_v.get());
          REQUIRE(set_neutral);
          REQUIRE(tree.get(z) == z_v.get());
        }
        AND_WHEN("add same values again") {
          auto again_positive = tree.add(i, i_v.get());
          auto again_negative = tree.add(j, j_v.get());
          auto again_neutral = tree.add(z, j_v.get());
          THEN("it should indicate that add is failed") {
            REQUIRE_FALSE(again_positive);
            REQUIRE_FALSE(again_negative);
            REQUIRE_FALSE(again_neutral);
          }
        }
        AND_WHEN("it remove the value") {
          auto rid_positive = tree.remove(i);
          auto rid_negative = tree.remove(j);
          auto rid_neutral = tree.remove(z);
          THEN("it should indicate the value is clean") {
            REQUIRE(rid_positive == i_v.get());
            REQUIRE_FALSE(tree.get(i));
            REQUIRE(rid_negative == j_v.get());
            REQUIRE_FALSE(tree.get(j));
            REQUIRE(rid_neutral == z_v.get());
            REQUIRE_FALSE(tree.get(z));
          }
          AND_WHEN("it remove the same value again") {
            rid_positive = tree.remove(i);
            rid_negative = tree.remove(j);
            rid_neutral = tree.remove(z);
            THEN("it should indicate remove failed"){
              REQUIRE_FALSE(rid_positive);
              REQUIRE_FALSE(rid_negative);
              REQUIRE_FALSE(rid_neutral);
            }
          }
        }
      }
    }
  }

}

#endif // TEST
