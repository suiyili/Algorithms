#pragma once
#include <bitset>
#include <cmath>
#include <memory>
#include <utility>

#include "bit_reverse_array.h"

namespace fft::generic {

template <std::size_t N>
requires is_power_of_two<N> inline bit_reverse_array<N>::bit_reverse_array(
    const complex_array<N>& source)
    : source_(source) {}

template <std::size_t N>
requires is_power_of_two<N> inline const real_complex& bit_reverse_array<N>::operator[](
    std::size_t ordinal) const noexcept {
  return source_[reverse_indices_[ordinal]];
}

template<std::size_t N>
requires is_power_of_two<N>
inline std::size_t bit_reverse_array<N>::bit_length()
{
  static const std::size_t bit_len = (std::size_t)std::log2(N);
  return bit_len;
}

template <size_t N>
requires is_power_of_two<N> inline bit_reverse_array<N>::indices_array
bit_reverse_array<N>::create() {
  indices_array indices = {0};
  for (size_t i = 0; i < N; ++i) indices[i] = get_bit_reverse(i);
  return std::move(indices);
}

template <std::size_t N>
requires is_power_of_two<N> inline std::size_t
bit_reverse_array<N>::get_bit_reverse(std::size_t number) {
  auto bit_len = bit_length();

  std::bitset<sizeof(std::size_t)> count = number;
  for (std::size_t i = 0; i < bit_len / 2; ++i){
    auto j = bit_len - i - 1;
    auto t = count.test(i);
    count.set(i, count.test(j));
    count.set(j, t);
  }
  return count.to_ulong();
}

template <size_t N>
requires is_power_of_two<N> const typename bit_reverse_array<N>::indices_array
    bit_reverse_array<N>::reverse_indices_ = bit_reverse_array<N>::create();

}  // namespace fft::generic
