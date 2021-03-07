#pragma once

#include <array>
#include <cstddef>
#include <complex>

namespace fft::generic {

using real = double;

template<typename T>
const T pi = T(2 * std::acos(0.0));

using real_complex = std::complex<real>;

template <std::size_t N>
using complex_array = std::array<real_complex, N>;

template<std::size_t N>
concept is_power_of_two = requires {
  N && (N& (N - 1)) == 0;
};

}  // namespace fft::generic
