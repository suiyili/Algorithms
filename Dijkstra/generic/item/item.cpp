#include "item.hpp"
#include "generic/resource_manager/resource_manager.hpp"
#include <limits>

namespace graph::generic {
  item::item()
    :shortest_path_(nullptr), shortest_weight_(std::numeric_limits<int>::max()),
    children_(resource_manager::get_allocator<std::pair<item*, int>>())
  {
  }

  bool item::has_shortest_path() const
  {
    return shortest_path_;
  }

  bool item::update_shortest_path(item* parent, int weight)
  {
    weight += parent->shortest_weight_;
    auto shorter = weight < shortest_weight_;
    if(shorter) {
      shortest_path_ = parent;
      shortest_weight_ = weight;
      return true;
    }
    return false;
  }
  
  std::strong_ordering operator<=>(const item& lhs, const item& rhs)
  {
    return lhs.shortest_weight_ <=> rhs.shortest_weight_;
  }
  
  void add_link(item* from, item* to, int weight)
  {
    auto& children = from->children_;
    children.emplace_back(to, weight);
  }
  
}