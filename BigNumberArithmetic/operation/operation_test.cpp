#ifdef TEST

#include "operation.hpp"
#include <catch2/catch_test_macros.hpp>

namespace arithmetic {

SCENARIO("big number arithmetic domain model test", "[bignum]") {
  GIVEN("several big number") {
    WHEN("adding them") {
      bignum num_1(0x12);
      bignum num_2(0x33);
      bignum num_3(0x81);
      bignum num_4(0x02);
      THEN("it should return their sum") {
        REQUIRE((num_1 + ((num_2 + num_3) + num_4)) ==
                ((num_1 + num_2) + (num_3 + num_4)));
      }
    }

    WHEN("substracting amongst them") {
      bignum num_1(0x81);
      bignum num_2(0x33);
      bignum num_3(0x12);
      bignum num_4(0x02);
      THEN("it should do substract") {
        REQUIRE((num_1 - (num_2 - num_3) - num_4) ==
                ((num_1 - num_2) - (num_4 - num_3)));
      }
    }

    WHEN("mixing addition and substraction") {
      bignum num_1(0x08);
      bignum num_2(0x33, true);
      bignum num_3(0x12);
      bignum num_4(0x02, true);
      THEN("it should sum") {
        REQUIRE((num_1 - (num_2 + num_3) + num_4) ==
                ((num_1 - num_2) - (num_3 - num_4)));
      }
    }

    WHEN("mutiply others") {
      bignum num_1(0x08);
      bignum num_2(0x33, true);
      bignum num_3(0x02, true);

      THEN("it should do times") {
        const bignum product(0x08 * 0x33 * 0x02);
        REQUIRE((num_1 * num_2 * num_3) == product);
      }
    }

    WHEN("modulus others") {
      bignum num_1(0x88);
      bignum num_2(0x33);
      bignum num_3(0x02);
      THEN("it should get remainder") {
        const bignum remainder((0x88 % 0x33) % 0x02);
        REQUIRE(((num_1 % num_2) % num_3) == remainder);
      }
    }

    WHEN("divide others") {
      bignum num_1(0x88);
      bignum num_2(0x33);
      bignum num_3(0x02);
      THEN("it should get division") {
        const bignum division((0x88 / 0x33) / 0x02);
        REQUIRE(((num_1 / num_2) / num_3) == division);
      }
    }

    WHEN("do comprehensive operation") {
      bignum num_1(0x88);
      bignum num_2(0x33);
      bignum num_3(0x99);
      bignum num_4(0x22);

      THEN("it should get correct result") {
        const bignum result(0x88 - (0x88 / 0x33) * (0x99 % 0x22));
        REQUIRE((num_1 - (num_1 / num_2) * (num_3 % num_4)) == result);
      }
    }

    WHEN("do inverse operation") {
      bignum value(0x0E);
      bignum mod(0x57);
      bignum one(1U);
      THEN("it should get correct result") {
        bignum mod_inverse = value.mod_inverse_of(mod);
        REQUIRE(((mod_inverse * value) % mod) == one);
      }
    }
  }
}

} // namespace arithmetic
#endif // TEST