#include "fourier_transform.hpp"
#include <numbers>

namespace fft::transform {
real_complex fourier_transform::get_w(std::size_t n) const {
  const double angle = get_sign() * 2. * std::numbers::pi / n;
  return std::polar(1., angle);
}
} // namespace fft::transform