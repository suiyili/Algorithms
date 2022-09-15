#include "minimum_spanning_tree.hpp"
#include "generic/resource_manager/resource_manager.hpp"
#include <queue>

namespace tree::spanning_tree {

struct weight_connect {
  std::size_t from;
  std::size_t to;
  std::size_t weight;
};

static bool less(const weight_connect& lh, const weight_connect& rh);
static bool greater(const weight_connect& lh, const weight_connect& rh);

using node_set = std::pmr::unordered_set<std::size_t>;
using queue_buffer = std::pmr::vector<weight_connect>;
using weight_queue =
    std::priority_queue<weight_connect, queue_buffer, decltype(&less)>;

connect_set get_spanning_tree(const tree_retriever& tree, spanning_type type) {
  node_set nodes(tree.size(),
                 resource_manager::get_allocator<node_set::value_type>());
  connect_set connects(
      tree.size(), resource_manager::get_allocator<connect_set::value_type>());
  queue_buffer buffer(
      resource_manager::get_allocator<queue_buffer::value_type>());
  
  auto comp = type == spanning_type::minimum ? greater : less;

  weight_queue spanning_queue(comp, buffer);

  // start from id 0, dummy weight 0
  spanning_queue.push(weight_connect{0U, 0U});

  // tree has to be all connected, otherwise infinite loop.
  while (nodes.size() < tree.size()) {
    auto top = spanning_queue.top();
    spanning_queue.pop();    
    
    auto added = nodes.emplace(top.to);    
    if (!added.second) continue;

    connects.emplace(top.from, top.to);
    auto from = *added.first;
    for (auto to : tree.get_connected_nodes(from)) {
      auto weight = tree.get_weight({from, to});
      spanning_queue.push(weight_connect{from, to, weight});
    }
  }

  return connects;
}

bool less(const weight_connect& lh, const weight_connect& rh) {
  return lh.weight < rh.weight;
}

bool greater(const weight_connect& lh, const weight_connect& rh)
{
  return lh.weight > rh.weight;
}

}  // namespace tree::spanning_tree