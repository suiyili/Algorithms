#ifdef TEST

#include "cell_mock.hpp"

namespace game {

cell_mock::cell_mock(std::vector<bool>::reference increase_call,
                     std::vector<bool>::reference alive_call) noexcept
    : increase_called_(increase_call), alive_called_(alive_call) {}

bool cell_mock::alive() const noexcept {
  alive_called_ = true;
  return false;
}

void cell_mock::increase_neighbour() noexcept { increase_called_ = true; }

} // namespace game

#endif // TEST