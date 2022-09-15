#pragma once

#include "grid/grid.hpp"

namespace game {

class cell_i {
public:
  virtual ~cell_i() = default;

  virtual void increase_neighbour() = 0;
  virtual bool alive() const = 0;
};
} // namespace game