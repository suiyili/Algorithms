#include "generic/fft_types.hpp"
#include <initializer_list>
#include <vector>
#include <cstdlib>

using namespace fft::generic;

namespace fft::application {

using digit_unit = unsigned char;

 template <std::size_t N, std::size_t B> requires is_power_of_two<N> class bignum;

template <std::size_t N, std::size_t B>
 bignum<N, B> operator*(const bignum<N, B>& left, const bignum<N, B>& right);

template <std::size_t N, std::size_t B = 10U>
requires is_power_of_two<N> class bignum {
public:
  bignum(std::initializer_list<digit_unit> input);
  bignum(const complex_array<N> &input);
  std::vector<digit_unit> to_vector() const noexcept;

  template <std::size_t NN, std::size_t BB>
  friend bignum<NN, BB> operator* (const bignum<NN, BB> &left, const bignum<NN, BB>& right);

private:
  static complex_array<N>
  get_complex_array(std::initializer_list<digit_unit> input);
  const complex_array<N> data_;
};



} // namespace fft::application
