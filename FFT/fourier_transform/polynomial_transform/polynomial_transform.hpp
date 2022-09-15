#pragma once

#include "fourier_transform/fourier_transform.hpp"

namespace fft::transform {
class polynomial_transform : public fourier_transform
{
public:
  ~polynomial_transform() override = default;
private:
  // Inherited via fourier_transform
  real get_sign() const noexcept override;
  real get_coefficient(std::size_t n) const noexcept override;
};
}


