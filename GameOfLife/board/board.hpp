#pragma once

#include "cell/cell.hpp"
#include "cell_factory/cell_factory_i.hpp"
#include "grid/grid.hpp"
#include <vector>

namespace game {
class board final {
public:
  board(const std::vector<grid> &initial_cells);

  board(const board &) = delete;
  board(board &&) = delete;
  board &operator=(const board &) = delete;
  board &operator=(board &&) = delete;

  void generate_next(const cell_factory_i &cell_creator);

  const std::vector<grid> &get_cells() const;

private:
  std::vector<grid> living_cells_;
};

} // namespace game
