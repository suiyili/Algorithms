#include "inverse_transform.hpp"

namespace fft::transform {
  real inverse_transform::get_sign() const noexcept
  {
    return -1.;
  }
  real inverse_transform::get_coefficient(std::size_t n) const noexcept
  {
    return 1.0 / n;
  }
}