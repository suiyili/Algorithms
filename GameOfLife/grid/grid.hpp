#pragma once

#include <array>

namespace game {
class grid;
using neighbours = std::array<grid, 8>;

class grid {
public:
  grid(int x, int y) noexcept;
  grid(const grid &other) noexcept = default;
  grid &operator=(const grid &) = delete;
  grid &operator=(grid &&) = delete;

  friend bool operator==(const grid &left, const grid &right) noexcept;
  friend class grid_hash;

  friend class neighbour_factory;
  neighbours get_neighbours() const noexcept;

private:
  const int x_;
  const int y_;
};

class grid_hash final {
public:
  std::size_t operator()(const grid &g) const noexcept;
};

} // namespace game