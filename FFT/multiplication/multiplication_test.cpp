#ifdef TEST

#include "multiplication.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using namespace Catch::Matchers;

namespace fft::application {

  using decimal_bignum = bignum<8>;
  using hex_bignum = bignum<8, 16>;

  SCENARIO("test bignum multiplication", "[bignum, multiplication]")
  {
    GIVEN("an decimal bignum")
    {
      decimal_bignum num{ 1, 15, 3 }; //253
      WHEN("get its vector"){
        auto vec = num.to_vector();
        THEN("it should be regulated by its base") {
          REQUIRE_THAT(vec, Equals(std::vector<digit_unit>{3, 5, 2, 0, 0, 0, 0, 0}));
        }
      }
    }

    GIVEN("an decimal bignum")
    {
      hex_bignum num{ 0x12, 0xF, 0x4 }; //0x1FE4
      WHEN("get its vector")
      {
        auto vec = num.to_vector();
        THEN("it should be regulated by its base")
        {
          REQUIRE_THAT(vec, Equals(std::vector<digit_unit>{0x04, 0x0F, 0x02, 0x01, 0, 0, 0, 0}));
        }
      }
    }

    GIVEN("two decimal bignums") {
      decimal_bignum num1{ 8, 2, 3 }; //823
      decimal_bignum num2{ 5, 4, 7 }; //547

      WHEN("multiplicate them") {
        auto num_multiple = num1 * num2;
        THEN("it should get multiplication of two numbers") {
          auto vec = num_multiple.to_vector();
          REQUIRE_THAT(vec, Equals(std::vector<digit_unit>{1, 8, 1, 0, 5, 4, 0, 0}));
        }
      }
      

    }

    GIVEN("two hex bignums")
    {
      hex_bignum num1{ 0x1, 0xB, 0x9, 0x0 }; //7056
      hex_bignum num2{ 0x7, 0xE, 0xF }; //2031

      WHEN("multiplicate them")
      {
        auto num_multiple = num1 * num2;
        THEN("it should get multiplication of two numbers")
        {
          auto vec = num_multiple.to_vector();
          //expect 14,330,736
          REQUIRE_THAT(vec, Equals(std::vector<digit_unit>{0x0, 0x7, 0xB, 0xA, 0xA, 0xD, 0x0, 0x0}));
        }
      }


    }
  }
}

#endif // TEST
