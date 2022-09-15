#pragma once

#include <memory_resource>
#include <vector>
#include <utility>
#include <compare>

namespace graph::generic {
  class item
  {
  public:
    item();
    bool has_shortest_path() const;
    bool update_shortest_path(item* parent, int weight);
    item* shortest_path_;
    int shortest_weight_;
    std::pmr::vector<std::pair<item*, int>> children_;
  };

  std::strong_ordering operator <=> (const item& lhs, const item& rhs);
  void add_link(item* from, item* to, int weight);
}
