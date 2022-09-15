#pragma once

#include "generic/fft_types.hpp"

namespace fft::generic {
  template<std::size_t N> requires is_power_of_two<N>
  class bit_reverse_array
  {
  public:
    bit_reverse_array(const complex_array<N>& source);
    const real_complex& operator[] (std::size_t ordinal) const noexcept;

    static std::size_t bit_length();

  private:
    using indices_array = std::array<size_t, N>;
    static indices_array create();
    static std::size_t get_bit_reverse(std::size_t number);
    static const indices_array reverse_indices_;
    const complex_array<N>& source_;
  };

  template <std::size_t N>
  requires is_power_of_two<N>
    bit_reverse_array(const complex_array<N>& source)->bit_reverse_array<N>;

}