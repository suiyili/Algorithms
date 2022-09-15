#pragma once

#include "cell_i.hpp"

namespace game {
class cell final: public cell_i {
public:
  cell(bool exists) noexcept;

  cell(const cell &) = delete;
  cell &operator=(const cell &) = delete;
  cell(cell &&) = delete;
  cell &operator=(cell &&) = delete;

  void increase_neighbour() override;
  bool alive() const noexcept override;

private:
  const bool exists_;
  unsigned char number_of_neighbours_;
};
} // namespace game