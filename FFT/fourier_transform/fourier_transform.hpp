#pragma once

#include <algorithm>
#include <execution>

#include "generic/bit_reverse_array/bit_reverse_array.hpp"
#include "generic/fft_types.hpp"

using namespace fft::generic;

namespace fft::transform {
class fourier_transform {
 public:
  virtual ~fourier_transform() = default;
  template <std::size_t N>
  complex_array<N> transform(const complex_array<N>& values);

 private:
  virtual real get_sign() const = 0;
  virtual real get_coefficient(std::size_t n) const = 0;
  real_complex get_w(std::size_t n) const;
};

template <std::size_t N>
inline complex_array<N> fourier_transform::transform(
    const complex_array<N>& values) {
  complex_array<N> y;
  constexpr std::size_t half = N >> 1;
  std::array<std::size_t, half> parallel_pairs{0U};

  bit_reverse_array reverse_values(values);
  for (std::size_t i = 0; i < N; ++i) y[i] = reverse_values[i];

  auto bit_len = bit_reverse_array<N>::bit_length();
  for (std::size_t i = 0; i < bit_len; ++i) {
    auto n_2 = 0b01 << i;
    const auto n = n_2 << 1;
    const auto w_n = get_w(n);

    //construct pairs.
    std::size_t count = 0;
    for (std::size_t k = 0; k < N; k += n)
      for (std::size_t j = 0; j < n_2; ++j) parallel_pairs[count++] = k + j;
    //each pair exec in parallel 
    std::for_each(std::execution::unseq, parallel_pairs.cbegin(),
                  parallel_pairs.cend(), [&y, &w_n, &n_2](auto i) {
                    auto j = i + n_2;
                    auto w = std::pow(w_n, i);
                    auto u = y[i];
                    auto t = w * y[j];
                    y[i] = u + t;
                    y[j] = u - t;
                  });
  }

  auto coe = get_coefficient(N);
  for (auto& value : y) value *= coe;

  return std::move(y);
}

}  // namespace fft::transform