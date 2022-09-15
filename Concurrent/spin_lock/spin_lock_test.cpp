#ifdef TEST
#include <catch2/catch_test_macros.hpp>
#include "spin_lock.hpp"
#include <chrono>
#include <mutex>
#include <thread>

namespace concurrent {

SCENARIO("spin lock test", "[spin_lock]") {
  GIVEN("spin lock") {
    WHEN("init with true") {
      spin_lock spin_lock_v(true);

      THEN("it should block") { REQUIRE_FALSE(spin_lock_v.try_lock()); }
    }

    WHEN("init with false") {
      spin_lock spin_lock_v;

      THEN("it should not block") { REQUIRE(spin_lock_v.try_lock()); }
    }

    WHEN("multi-thread use try lock") {
      spin_lock spin_lock_v;
      size_t count = 0;

      auto worker = [&count, &spin_lock_v] {
        std::unique_lock lk(spin_lock_v, std::try_to_lock);
        if (lk) {
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
          ++count;
        }
      };
      std::thread th1(worker);
      std::thread th2(worker);
      th1.join();
      th2.join();
      THEN("it should action mutual exclusively") { REQUIRE(count == 1U); }
    }
  }

  WHEN("multi-thread use lock") {
    spin_lock spin_lock_v;
    size_t count = 0;

    auto worker = [&count, &spin_lock_v] {
      std::lock_guard lk(spin_lock_v);

      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      ++count;
    };
    std::thread th1(worker);
    std::thread th2(worker);
    th1.join();
    th2.join();
    THEN("it should action mutual exclusively") { REQUIRE(count == 2U); }
  }
}
}  // namespace concurrent
#endif  // TEST