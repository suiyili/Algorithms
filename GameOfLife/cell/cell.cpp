#include "cell.hpp"
#include <tuple>
#include <stdexcept>

namespace game {
cell::cell(bool exists) noexcept: exists_(exists), number_of_neighbours_(0) {}

void cell::increase_neighbour() {
  if (number_of_neighbours_ == std::tuple_size<neighbours>::value)
    throw std::out_of_range("can not have more than 8 neighbours");
  ++number_of_neighbours_;
}

bool cell::alive() const noexcept{
  const bool three_alive = number_of_neighbours_ == 3;
  const bool living_with_two = exists_ && number_of_neighbours_ == 2;
  return three_alive || living_with_two;
}
} // namespace game