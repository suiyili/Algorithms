#pragma once

#include "cell_factory_i.hpp"

namespace game {

class cell_factory final : public game::cell_factory_i {
public:
  cell_factory() = default;
  cell_factory(const cell_factory &&) = delete;
  cell_factory &operator=(const cell_factory &) = delete;
  cell_factory(cell_factory &&) = delete;
  cell_factory &operator=(cell_factory &&) = delete;

  std::unique_ptr<cell_i> create(bool exists) const override;
};

} // namespace game