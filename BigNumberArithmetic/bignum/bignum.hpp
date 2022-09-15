#pragma once

#include "generic/bits_value/bits_value.hpp"

using namespace generic;

namespace arithmetic {
class bignum final {
public:
  bignum() noexcept = default;
  explicit bignum(size_t value, bool sign = false) noexcept;
  explicit bignum(bits_value &&value, bool sign = false) noexcept;
  ~bignum() = default;

  bignum(const bignum &other) noexcept;
  bignum(bignum &&other) noexcept;

  bignum &operator=(const bignum &other) noexcept;
  bignum &operator=(bignum &&other) noexcept;

  bignum &operator+=(const bignum &added);
  bignum &operator-=(const bignum &removed);
  bignum &operator*=(const bignum &times);
  bignum &operator%=(const bignum &divisor);
  bignum &operator/=(const bignum &divisor);
  bignum &power(unsigned short exponent);

  const bignum operator++(int);
  bignum &operator++();
  const bignum operator--(int);
  bignum &operator--();

  bignum mod_inverse_of(const bignum &mod) const;

  size_t size();

  friend bool operator==(const bignum &left, const bignum &right);

private:
  bignum &sum(const bignum &value, bool same_sign);

  void join_sign(bool other_sign);

  bits_value value_;
  bool sign_;
};
} // namespace arithmetic