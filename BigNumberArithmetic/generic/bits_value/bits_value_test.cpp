#ifdef TEST

#include "bits_value.hpp"
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>

namespace generic {

SCENARIO("bits value test", "[bits_value]") {
  GIVEN("a hex array") {
    WHEN("construct with hex array more than capacity") {
      std::valarray<unsigned char> value(0x01, capacity / 8 + 1);
      auto ctor = [&value] { bits_value big_value(value); };
      THEN("it will throw") {
        REQUIRE_THROWS_AS(ctor(), std::invalid_argument);
      }
    }

    WHEN("construct a bits value with hex array") {
      bits_value big_value({0x33, 0x12});

      size_t v = 0x33;
      v <<= 8;
      v |= 0x12;

      THEN("it will have a hex value") {
        big_bits expected(v);

        REQUIRE(big_value == expected);
      }
    }
  }

  GIVEN("a bits value") {
    WHEN("get bits span") {
      bits_value big_value(0b110101001);
      THEN("it will return the span from most left bit") {
        REQUIRE(big_value.bits_span() == 9);
      }
    }

    WHEN("overflow with shift") {
      bits_value big_value(0b1111);
      bits_value very_large(0x01);
      very_large = ~very_large;
      THEN("it will throw") {
        REQUIRE_THROWS_AS(big_value *= very_large, std::overflow_error);
      }
    }

    WHEN("check adding overflow") {
      bits_value v1, v2(0b1111);
      v1.set();
      THEN("it will return if it is overflow") {
        REQUIRE(v1.check_adding_overflow(v2));
        REQUIRE_FALSE(v2.check_adding_overflow(v2));
      }
    }
  }

  GIVEN("a bits value") {
    WHEN("add one") {
      bits_value big_value(0b11111);
      THEN("it will flip from start until 0 occur") {
        bits_value expected(0b100000);
        REQUIRE(++big_value == expected);
      }
    }

    AND_WHEN("take away one") {
      bits_value big_value(0b10000);
      THEN("it will flip from start until 1 occur") {
        bits_value expected(0b1111);
        REQUIRE(--big_value == expected);
      }
    }

    AND_WHEN("divided by 0") {
      bits_value num(0x03);
      bits_value denominator(0);
      THEN("it will throw") {
        REQUIRE_THROWS_AS(divide(num, denominator), std::overflow_error);
      }
    }
  }

  GIVEN("two bits value") {
    size_t a = 0b110101001;
    size_t b = 0b110101011;

    bits_value smaller(a);
    bits_value bigger(b);
    WHEN("compare them") {
      THEN("it will return if one is less than another") {
        REQUIRE(smaller < bigger);
      }
    }

    AND_WHEN("add them") {
      smaller += bigger;
      THEN("it will return sum") { REQUIRE(smaller == a + b); }
    }
    AND_WHEN("big substract small") {
      bigger -= smaller;
      THEN("it should return substract result") {
        bits_value result(b - a);
        REQUIRE(bigger == result);
      }
    }
    AND_WHEN("small reverse substract big") {
      smaller.reverse_substract(bigger);
      THEN("it should return substract result") {
        bits_value result(b - a);
        REQUIRE(smaller == result);
      }
    }
    AND_WHEN("multiply them") {
      smaller *= bigger;
      THEN("it should return substract result") {
        bits_value result(b * a);
        REQUIRE(smaller == result);
      }
    }
    AND_WHEN("small one divided by bigger one") {
      auto divided = divide(smaller, bigger).first;
      THEN("it will return 0") {
        bits_value result(0);
        REQUIRE(divided == result);
      }
    }
    AND_WHEN("bigger one divided by smaller one") {
      auto mod = divide(bigger, smaller).second;
      THEN("mod will return remainder") {
        bits_value result(b % a);
        REQUIRE(mod == result);
      }
    }

    AND_WHEN("smaller divided by bigger") {
      auto mod = divide(smaller, bigger).second;

      THEN("the mod will keep the smaller value") {
        bits_value remainder(a % b);
        REQUIRE(mod == remainder);
      }
    }
  }
}

} // namespace arithmetic
#endif // TEST
