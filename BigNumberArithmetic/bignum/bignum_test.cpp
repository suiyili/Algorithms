#ifdef TEST

#include "bignum.hpp"
#include "../generic/coprime_error.hpp"
#include <catch2/catch_test_macros.hpp>

namespace arithmetic {
SCENARIO("big number test", "[bignum]") {
  GIVEN("a maxium number") {
    bits_value v;
    v = ~v;
    bignum num(move(v));
    WHEN("increase a maximum number") {
      THEN("it will throw") { REQUIRE_THROWS_AS(++num, std::overflow_error); }
    }
  }

  GIVEN("a minimum number") {
    WHEN("decrease it") {
      bits_value v;
      v.set();

      bignum num(move(v), true);
      THEN("it will throw") { REQUIRE_THROWS_AS(--num, std::underflow_error); }
    }
  }

  GIVEN("a positive number") {
    unsigned long long value = 0b1100100111;
    bignum num(value);

    WHEN("increasing it") {
      ++num;
      THEN("it adds one") {
        ++value;
        bignum increase(value);
        REQUIRE(num == increase);
      }
    }

    AND_WHEN("decreasing it") {
      --num;
      THEN("it takes away one") {
        --value;
        bignum increase(value);
        REQUIRE(num == increase);
      }
    }

    AND_WHEN("divided by 0") {
      bignum divisor;

      THEN("it will throw") {
        REQUIRE_THROWS_AS(num /= divisor, std::overflow_error);
      }
    }

    AND_WHEN("power with 0") {
      num.power(0);
      THEN("it should return 1") {
        bignum powered(0x01);
        REQUIRE(num == powered);
      }
    }

    AND_WHEN("mod a negative denominator") {
      bignum denominator(0x02, true);
      THEN("it will throw") {
        REQUIRE_THROWS_AS(num %= denominator, std::invalid_argument);
      }
    }
  }

  GIVEN("a negative number") {
    unsigned long long value = 0b1100100000;
    bignum num(value, true);
    WHEN("increasing") {
      ++num;
      THEN("it adds one") {
        --value;
        bignum increased(value, true);
        REQUIRE(num == increased);
      }
    }

    WHEN("decreasing it") {
      --num;
      THEN("it takes away one") {
        ++value;
        bignum decreased(value, true);
        REQUIRE(num == decreased);
      }
    }

    WHEN("do power with even number") {
      num.power(4);
      THEN("it should return result of power") {
        bignum powered((size_t)pow(value, 4));
        REQUIRE(num == powered);
      }
    }

    WHEN("do power with odd number") {
      num.power(3);
      THEN("it should return result of power") {
        bignum powered((size_t)pow(value, 3), true);
        REQUIRE(num == powered);
      }
    }

    WHEN("do mod with negative") {
      bignum denominator(0x08);
      num %= denominator;
      THEN("it should return the remainder") {
        bignum remainder(value % 0x08, true);
        REQUIRE(num == remainder);
      }
    }
  }

  GIVEN("two positive numbers") {
    bignum num_bigger(0x33);
    bignum num_smaller(0x12);

    AND_WHEN("small one substructs larger one") {
      num_smaller -= num_bigger;

      THEN("it should return a negative number") {
        bignum sum(0x33 - 0x12, true);
        REQUIRE(num_smaller == sum);
      }
    }
  }

  GIVEN("one positive and one negative numbers") {
    bignum num_positive(0x33);
    bignum num_negative(0x12, true);

    WHEN("add them") {
      num_positive += num_negative;
      THEN("it should return sum") {
        bignum sum(0x33 - 0x12);
        REQUIRE(num_positive == sum);
      }
    }
    AND_WHEN("positive substructing negative") {
      num_positive -= num_negative;
      THEN("it should return the nagative sum") {
        bignum sum(0x33 + 0x12);
        REQUIRE(num_positive == sum);
      }
    }
    AND_WHEN("negative substructing positive") {
      num_negative -= num_positive;
      THEN("it should return the remaining") {
        bignum sum(0x33 + 0x12, true);
        REQUIRE(num_negative == sum);
      }
    }
    AND_WHEN("multiplying them") {
      num_positive *= num_negative;
      THEN("it should return negative product") {
        bignum product(0x33 * 0x12, true);
        REQUIRE(num_positive == product);
      }
    }

    AND_WHEN("positive divide by negative") {
      num_positive /= num_negative;
      THEN("it should return negative") {
        bignum result(0x33 / 0x12, true);
        REQUIRE(num_positive == result);
      }
    }
  }

  GIVEN("two negative numbers") {
    bignum num(0x33, true);
    bignum num_op(0x12, true);

    WHEN("multiplying") {
      num *= num_op;
      THEN("it should return positive product") {
        bignum product(0x33 * 0x12);
        REQUIRE(num == product);
      }
    }

    AND_WHEN("dividing") {
      num /= num_op;
      THEN("it should return positive result") {
        bignum result(0x33 / 0x12);
        REQUIRE(num == result);
      }
    }
  }

  GIVEN("two big numbers") {
    bits_value v1(0b01);
    bits_value v2(0b01);
    v1 <<= v1.size() - 1;
    v2 <<= v2.size() - 1;
    bignum num_left(move(v1));
    bignum num_right(move(v2));
    WHEN("adding them") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(num_left += num_right, std::overflow_error);
      }
    }
    AND_WHEN("multiply them") {
      THEN("it will throw overflow") {
        REQUIRE_THROWS_AS(num_left *= num_right, std::overflow_error);
      }
    }
  }

  GIVEN("two numbers have no co-prime") {
    bignum num1;
    bignum mod1;
    bignum num2(0x33);
    bignum mod2(0x33, true);
    WHEN("get inverse modular without co-prime") {
      THEN("it will throw") {
        REQUIRE_THROWS_AS(num1.mod_inverse_of(mod1), coprime_error);
        REQUIRE_THROWS_AS(num2.mod_inverse_of(mod2), coprime_error);
      }
    }
  }

  GIVEN("two same non-zero numbers") {
    bignum num1(1);
    bignum mod1(1);
    WHEN("get inverse modular") {
      THEN("it will return 1") {
        bignum inverse1(1);
        REQUIRE(num1.mod_inverse_of(mod1) == inverse1);
      }
    }
  }

  GIVEN("two number with co-prime") {
    bignum num3(22, true);
    bignum mod3(57, true);
    WHEN("get inverse modular") {
      THEN("it will return the inverse modular") {
        bignum inverse3(13, true);
        REQUIRE(num3.mod_inverse_of(mod3) == inverse3);
      }
    }
  }
}
} // namespace arithmetic

#endif // TEST
