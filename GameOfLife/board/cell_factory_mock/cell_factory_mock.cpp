#ifdef TEST


#include "cell_factory_mock.hpp"
#include "board/cell_mock/cell_mock.hpp"

namespace game {

std::unique_ptr<cell_i> cell_factory_mock::create(bool exists) const {
  ++create_called_;
  cell_increase_.push_back(false);
  cell_alive_.push_back(false);

  return std::make_unique<cell_mock>(cell_increase_.back(), cell_alive_.back());
}

size_t cell_factory_mock::create_called() const noexcept {
  return create_called_;
}

bool cell_factory_mock::all_cells_increase_called() noexcept {
  bool all_called = true;
  for (auto b : cell_increase_)
    all_called &= b;

  return all_called;
}

bool cell_factory_mock::all_cells_alive_called() noexcept {
  bool all_called = true;
  for (auto b : cell_alive_)
    all_called &= b;

  return all_called;
}

} // namespace game

#endif // TEST