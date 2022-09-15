#pragma once

#include <bitset>
#include <ranges>

namespace tree::generic {

constexpr unsigned int bit_length = sizeof(unsigned int) * 8U;
using bitset_int = std::bitset<bit_length>;
auto get_bit_indices() {
  static_assert(bit_length > 0);
  return std::views::iota(0U, bit_length) | std::views::reverse;
}

} // namespace tree::generic
