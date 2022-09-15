#include "polynomial_transform.hpp"

using namespace std::complex_literals;

namespace fft::transform {
  real polynomial_transform::get_sign() const noexcept
  {
    return 1.0;
  }
  real polynomial_transform::get_coefficient(std::size_t n) const noexcept
  {
    return 1.0;
  }
}