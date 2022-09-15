#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include "minimum_spanning_tree.hpp"

namespace tree::spanning_tree {

  SCENARIO("minimum spanning tree test", "[minimum_spanning_tree]"){
    GIVEN("a connected graph"){
      tree_retriever graph(9U);
      graph.set({ 0, 1 }, 4U);
      graph.set({ 1, 2 }, 8U);
      graph.set({ 2, 3 }, 7U);
      graph.set({ 3, 4 }, 9U);
      graph.set({ 4, 5 }, 10U);
      graph.set({ 5, 6 }, 2U);
      graph.set({ 6, 7 }, 1U);
      graph.set({ 7, 8 }, 7U);
      graph.set({ 0, 7 }, 9U);
      graph.set({ 7, 1 }, 11U);
      graph.set({ 8, 2 }, 2U);
      graph.set({ 6, 8 }, 6U);
      graph.set({ 5, 2 }, 4U);
      graph.set({ 3, 5 }, 14U);

      WHEN("get minimum spanning tree"){
        auto minimum_spanning = get_spanning_tree(graph, spanning_type::minimum);
     
        THEN("it should give the minimum spanning tree"){
          REQUIRE(minimum_spanning.contains({ 0, 1 }));
          REQUIRE(minimum_spanning.contains({ 1, 2 }));
          REQUIRE(minimum_spanning.contains({ 2, 8 }));
          REQUIRE(minimum_spanning.contains({ 2, 5 }));
          REQUIRE(minimum_spanning.contains({ 5, 6 }));
          REQUIRE(minimum_spanning.contains({ 3, 2 }));
          REQUIRE(minimum_spanning.contains({ 3, 4 }));

          REQUIRE_FALSE(minimum_spanning.contains({ 0, 7 }));
          REQUIRE_FALSE(minimum_spanning.contains({ 1, 7 }));
          REQUIRE_FALSE(minimum_spanning.contains({ 8, 7 }));
          REQUIRE_FALSE(minimum_spanning.contains({ 8, 6 }));
          REQUIRE_FALSE(minimum_spanning.contains({ 4, 5 }));
          REQUIRE_FALSE(minimum_spanning.contains({ 3, 5 }));

        }
      }
    }
  
  }

}

#endif // TEST
