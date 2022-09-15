#include "shortest_path.hpp"
#include "generic/priority_queue/priority_queue.hpp"
#include <unordered_set>

namespace graph {
item *compute_shortest_path(item *source) {

  priority_queue<item> candidates;
  source->shortest_path_ = source;
  source->shortest_weight_ = 0;
  candidates.push(source);

  while (auto top = candidates.pop()) {
    for (auto [child, weight] : top->children_) {
      auto has_shortest = child->has_shortest_path();
      if (child->update_shortest_path(top, weight)) {
        if (has_shortest)
          candidates.update(child);
        else
          candidates.push(child);
      }
    }
  }
  return source;
}
} // namespace graph