#include "grid.hpp"
#include <functional>

namespace game {
grid::grid(int x, int y) noexcept: x_(x), y_(y) {}

neighbours grid::get_neighbours() const noexcept{
  return {grid(x_ + 1, y_),     grid(x_ - 1, y_),     grid(x_, y_ + 1),
          grid(x_, y_ - 1),     grid(x_ + 1, y_ + 1), grid(x_ - 1, y_ - 1),
          grid(x_ - 1, y_ + 1), grid(x_ + 1, y_ - 1)};
}

bool operator==(const grid &left, const grid &right) noexcept{
  return (left.x_ == right.x_) && (left.y_ == right.y_);
}

size_t grid_hash::operator()(const grid &g) const noexcept{
  std::hash<int> hash_fn;
  const auto h1 = hash_fn(g.x_);
  const auto h2 = hash_fn(g.y_);
  return h1 ^ (h2 << 1);
}
} // namespace game
