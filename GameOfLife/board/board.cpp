#include "board.hpp"
#include <memory>
#include <unordered_map>

namespace game {
board::board(const std::vector<grid> &initial_cells)
    : living_cells_(initial_cells) {}

void board::generate_next(const cell_factory_i &cell_creator) {
  std::unordered_map<grid, std::unique_ptr<cell_i>, grid_hash> cells;

  for (auto &g : living_cells_)
    cells.emplace(g, cell_creator.create(true));

  for (auto &g : living_cells_) {
    const auto neighbours_v = g.get_neighbours();
    for (const auto &neighbour : neighbours_v) {
      auto found = cells.find(neighbour);
      if (found == cells.end()) {
        auto c = cells.emplace(neighbour, cell_creator.create(false));
        found = c.first;
      }
      auto &c = found->second;
      c->increase_neighbour();
    }
  }

  living_cells_.clear();
  living_cells_.reserve(cells.size());
  for (auto &c : cells) {
    const auto &cell_v = c.second;
    if (cell_v->alive())
      living_cells_.emplace_back(c.first);
  }
}

const std::vector<grid> &board::get_cells() const { return living_cells_; }

} // namespace game