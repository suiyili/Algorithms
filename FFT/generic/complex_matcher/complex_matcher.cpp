#ifdef TEST

#include "complex_matcher.hpp"

using namespace Catch;

namespace fft::generic {
  complex_matcher::complex_matcher(real_complex value, real precision)
    :precision_(precision), value_(std::move(value))
  {}

  std::string complex_matcher::describe() const
  {
    return "complex value not match";
  }

  bool complex_matcher::match(const real_complex& other) const
  {
    return value_.real() == Catch::Approx(other.real()).margin(precision_)
          && value_.imag() == Catch::Approx(other.imag()).margin(precision_);
  }

  complex_matcher equal_to(const real_complex& value, real precision)
  {
    return complex_matcher(value, precision);
  }

}

#endif // TEST