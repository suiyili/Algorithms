#include "cell_factory.hpp"
#include "cell/cell.hpp"

namespace game {
std::unique_ptr<cell_i> cell_factory::create(bool exists) const {
  return std::make_unique<cell>(exists);
}

} // namespace game
