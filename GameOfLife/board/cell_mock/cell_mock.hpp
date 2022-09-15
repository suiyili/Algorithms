#pragma once

#include "cell/cell_i.hpp"
#include <vector>

namespace game {

class cell_mock final : public cell_i {
public:
  cell_mock(std::vector<bool>::reference increase_call,
            std::vector<bool>::reference alive_call) noexcept;

  bool alive() const noexcept override;
  void increase_neighbour() noexcept override;

private:
  std::vector<bool>::reference increase_called_;
  mutable std::vector<bool>::reference alive_called_;
};

} // namespace game