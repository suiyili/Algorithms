#ifdef TEST

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include "tree_retriever.hpp"

using namespace Catch;
using namespace Catch::Matchers;

namespace tree::spanning_tree {

  SCENARIO("connect tree test", "[tree_retriever]"){

    GIVEN("size is 1"){
      WHEN("build tree"){
        auto ctor = [] {tree_retriever m(1); };
        THEN("it should throw"){
          REQUIRE_THROWS_AS(ctor(), std::logic_error);
        }
      }
    }
   
    GIVEN("a connect tree with a max size"){
      tree_retriever tree(15U);
      AND_GIVEN("a pair of same points")
      {
        WHEN("add it to a tree")
        {
          tree.set({ 1, 1 }, 20U);
          THEN("it will keep zero")
          {
            tree::generic::connect conn{ 1, 1 };
            REQUIRE(tree.get_weight(conn) == 0U);
          }
        }
      }

      AND_GIVEN("a pair of out of length points")
      {
        WHEN("add it to a tree")
        {
          tree.set({ 15, 1 }, 20U);
          THEN("its weight will be zero")
          {
            tree::generic::connect conn{ 1, 15 };
            REQUIRE(tree.get_weight(conn) == 0U);
          }
        }
      }
      AND_GIVEN("a distinct pair of points"){
        size_t parent = 1;
        WHEN("add it to a tree"){
          tree.set({ 8, parent }, 20U);        
          THEN("get the value is same as the setting"){
            tree::generic::connect conn{ parent, 8};
            REQUIRE(tree.get_weight(conn) == 20U);
          }
          THEN("other pair will keep 0 weight"){
            tree::generic::connect conn{ 2, 8 };
            REQUIRE(tree.get_weight(conn) == 0U);
          }
          AND_WHEN("add another node shared connected to one of node")
          {
            tree.set({ parent, 9 }, 10U);
            THEN("it should get all nodes connected to the share node")
            {
              auto nodes = tree.get_connected_nodes(parent);
              std::vector<unsigned long>
              actual(nodes.begin(), nodes.end());
              decltype(actual) expected = { 8, 9 };
              REQUIRE_THAT(expected, UnorderedEquals<std::size_t>(actual));
            }
          }
        }
      }
      
    
    }
  }
}
#endif // TEST
