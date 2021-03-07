#pragma once

#ifdef TEST

#include <catch2/catch.hpp>
#include "fft_types.hpp"

using namespace Catch;

namespace fft::generic {

class complex_matcher : public MatcherBase<real_complex>
{
public:
  complex_matcher(real_complex value, real precision);

  std::string describe() const override;
  bool match(const real_complex& other) const override;
private:
  const real_complex value_;
  const real precision_;
};

complex_matcher equal_to(const real_complex& value, real precision);

}
#endif // TEST



