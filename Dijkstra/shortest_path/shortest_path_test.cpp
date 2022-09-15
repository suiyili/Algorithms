#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "shortest_path.hpp"

using namespace graph::generic;

namespace graph {
SCENARIO("shortest path finder test", "[shortest_path_finder]") {
  GIVEN("a graph") {
    auto s = std::make_unique<item>();
    auto t = std::make_unique<item>();
    auto x = std::make_unique<item>();
    auto y = std::make_unique<item>();
    auto z = std::make_unique<item>();

    add_link(s.get(), t.get(), 10);
    add_link(t.get(), x.get(), 1);
    add_link(t.get(), y.get(), 2);
    add_link(s.get(), y.get(), 5);
    add_link(y.get(), t.get(), 3);
    add_link(y.get(), x.get(), 9);
    add_link(y.get(), z.get(), 2);
    add_link(x.get(), z.get(), 4);
    add_link(z.get(), x.get(), 6);
    add_link(z.get(), s.get(), 7);

    WHEN("compute shortest path") {
      auto source = compute_shortest_path(s.get());
      THEN("it should set each vertex shortest path") {
        
        REQUIRE(s->shortest_path_ == source);
        REQUIRE(s->shortest_weight_ == 0);

        REQUIRE(y->shortest_path_ == s.get());
        REQUIRE(y->shortest_weight_ == 5);        

        REQUIRE(t->shortest_path_ == y.get());
        REQUIRE(t->shortest_weight_ == 8);
        
        REQUIRE(z->shortest_path_ == y.get());
        REQUIRE(z->shortest_weight_ == 7);

        REQUIRE(x->shortest_path_ == t.get());
        REQUIRE(x->shortest_weight_ == 9);
      }
    }
  }
}
} // namespace graph

#endif // TEST