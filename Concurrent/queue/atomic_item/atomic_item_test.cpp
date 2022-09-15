#ifdef TEST

#include <atomic>

#include <catch2/catch_test_macros.hpp>
#include "atomic_item.hpp"

namespace concurrent {

SCENARIO("atomic item test", "[atomic_item]") {
  GIVEN("a empty atomic_item") {
    atomic_item item;
    WHEN("put an item to it") {
      int input = 1;
      auto put = item.put(&input);
      THEN("it should be ok") { REQUIRE(put); }
    }
    AND_WHEN("take out an item") {
      void* output = nullptr;
      auto taken = item.take(output);
      THEN("it should fail") { REQUIRE_FALSE(taken); }
    }
  }

  GIVEN("atomic_item with an item in it") {
    atomic_item item;
    int input = 1;
    CHECK(item.put(&input));
    WHEN("take the item out") {
      void* output = nullptr;
      auto taken = item.take(output);
      THEN("it should be the input one") {
        REQUIRE(taken);
        REQUIRE(output == &input);
      }
    }
    AND_WHEN("put another item in") {
      int j = 2;
      auto put = item.put(&j);
      THEN("it will fail") { REQUIRE_FALSE(put); }
    }
    AND_WHEN("take the item twice") {
      void* j = nullptr;
      auto taken = item.take(j);
      CHECK(taken);
      taken = item.take(j);
      THEN("it will fail the second time") { REQUIRE_FALSE(taken); }
    }
  }
}

}  // namespace concurrent
#endif  // TEST