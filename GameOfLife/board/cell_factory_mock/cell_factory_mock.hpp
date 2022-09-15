#pragma once

#include "cell_factory/cell_factory_i.hpp"
#include <vector>

namespace game {

class cell_factory_mock final : public cell_factory_i {
public:
  std::unique_ptr<cell_i> create(bool exists) const override;
  size_t create_called() const noexcept;
  bool all_cells_increase_called() noexcept;
  bool all_cells_alive_called() noexcept;

private:
  mutable size_t create_called_ = 0;
  mutable std::vector<bool> cell_increase_;
  mutable std::vector<bool> cell_alive_;
};

} // namespace game