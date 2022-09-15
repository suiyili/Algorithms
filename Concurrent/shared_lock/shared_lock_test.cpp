#ifdef TEST
#include "shared_lock.hpp"
#include <catch2/catch_test_macros.hpp>
#include <mutex>
#include <shared_mutex>
#include <thread>

namespace concurrent {

SCENARIO("shared lock test", "[shared_lock]") {
  GIVEN("shared lock") {
    WHEN("multi-thread use lock to write") {
      shared_lock shared;
      size_t count = 0;

      auto worker = [&count, &shared] {
        std::unique_lock lk(shared);
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

  WHEN("multi-thread shared lock to read") {
    shared_lock shared;
    std::atomic_size_t source = 0U;
	size_t count = 0U;

    auto worker_1 = [&source, &shared](size_t& out) {
      std::shared_lock lk(shared);
	  ++source;
	  //wait for another in
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
	  out = source;
    };

	auto worker_2 = [&source, &shared]() {
		std::shared_lock lk(shared);
		++source;
	};

    std::thread th1(worker_1, std::ref(count));
    std::thread th2(worker_2);
    th1.join();
    th2.join();
    THEN("it should share the resource") { 
		REQUIRE(count == 2U);
	}
  }

  WHEN("multi-thread write then read") {
	  shared_lock shared;
	  size_t source = 9U;
	  size_t out = 0U;
	  std::atomic_bool ready = false;

	  auto read_worker = [&source, &shared, &ready](size_t& id) {
		  //wait for write happen first
		  while (!ready.load(std::memory_order_relaxed))
			  ;
		  std::shared_lock lk(shared);		  
		  id = source;
	  };

	  auto write_worker = [&source, &shared, &ready] {
		  std::unique_lock lk(shared);
		  ready.store(true, std::memory_order_release);
		  //wait for read lock happen
		  std::this_thread::sleep_for(std::chrono::milliseconds(1));
		  ++source;
	  };

	  std::thread write_th(write_worker);
	  std::thread read_th(read_worker, std::ref(out));

	  read_th.join();
	  write_th.join();
	  THEN("it should read the updated value") {
		  REQUIRE(out == source);
	  }
  }

  WHEN("multi-thread read then write") {
	  shared_lock shared;
	  size_t source = 9U, prev = source;
	  size_t out = 0U;
	  std::atomic_bool ready = false;

	  auto read_worker = [&source, &shared, &ready](size_t& id) {
		  std::shared_lock lk(shared);
		  ready.store(true, std::memory_order_release);
		  std::this_thread::sleep_for(std::chrono::milliseconds(1));
		  id = source;
	  };

	  auto write_worker = [&source, &shared, &ready] {
		  while (!ready.load(std::memory_order_relaxed))
			  ;
		  std::unique_lock lk(shared);		 
		  ++source;
	  };

	  std::thread read_th(read_worker, std::ref(out));
	  std::thread write_th(write_worker);
	  read_th.join();
	  write_th.join();
	  THEN("it should read the updated value") {
		  REQUIRE(out == prev);
	  }
  }
}

}  // namespace concurrent
#endif  // TEST