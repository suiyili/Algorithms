#pragma once

#include "cell/cell_i.hpp"
#include <memory>

namespace game {

class cell_factory_i {
public:
  virtual ~cell_factory_i() = default;
  virtual std::unique_ptr<cell_i> create(bool exists) const = 0;
};

} // namespace game