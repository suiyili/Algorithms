#pragma once

#include "multiplication.h"
#include "fourier_transform/polynomial_transform/polynomial_transform.hpp"
#include "fourier_transform/inverse_transform/inverse_transform.hpp"
#include <utility>

using namespace fft::transform;

namespace fft::application {

template <std::size_t N, std::size_t B>
requires is_power_of_two<N> inline bignum<N, B>::bignum(
    std::initializer_list<digit_unit> input)
    : data_(get_complex_array(std::move(input))) {}

template <std::size_t N, std::size_t B>
requires is_power_of_two<N> inline bignum<N, B>::bignum(
    const complex_array<N> &input)
    : data_(input) {}

template <std::size_t N, std::size_t B>
requires is_power_of_two<N> inline std::vector<digit_unit>
bignum<N, B>::to_vector() const noexcept {

  std::vector<digit_unit> number;
  number.reserve(data_.size());
  std::size_t to_higher = 0;
  for (auto &c : data_) {
    auto digit = (std::size_t)std::round(c.real());
    digit += to_higher;
    to_higher = digit / B;
    number.push_back(digit % B);
  }

  return number;
}

template <std::size_t N, std::size_t B>
requires is_power_of_two<N> inline complex_array<N>
bignum<N, B>::get_complex_array(std::initializer_list<digit_unit> input) {
  std::vector<digit_unit> real_group(std::rbegin(input), std::rend(input));
  complex_array<N> buffer{{0, 0}};
  auto len = std::min(real_group.size(), N);
  for (std::size_t i = 0; i < len; ++i)
    buffer[i] = real_complex(real_group[i], 0.0);
  return std::move(buffer);
}

template <std::size_t N, std::size_t B>
bignum<N, B> operator*(const bignum<N, B> &left,
                              const bignum<N, B> &right) {
  polynomial_transform poly;
  auto left_trans = poly.transform(left.data_);
  auto right_trans = poly.transform(right.data_);
  complex_array<N> product;
  for (size_t i = 0; i < product.size(); ++i)
    product[i] = left_trans[i] * right_trans[i];

  inverse_transform inverse;
  auto multiplication = inverse.transform(product);
  
  return bignum<N, B>{multiplication};
 
}
} // namespace fft::application