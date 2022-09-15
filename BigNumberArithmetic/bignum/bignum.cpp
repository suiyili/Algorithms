#include "bignum.hpp"
#include "../generic/coprime_error.hpp"
#include <memory>

namespace arithmetic {
bignum::bignum(size_t value, bool sign) noexcept: value_(value), sign_(sign) {}

bignum::bignum(bits_value &&value, bool sign) noexcept
    : value_(std::move(value)), sign_(sign) {}

bignum::bignum(const bignum &other) noexcept
    : value_(other.value_), sign_(other.sign_) {}

bignum::bignum(bignum &&other) noexcept
    : value_(std::move(other.value_)), sign_(other.sign_) {}

bignum &bignum::operator=(const bignum &other) noexcept {
  if (&other != this) {
    value_ = other.value_;
    sign_ = other.sign_;
  }
  return *this;
}

bignum &bignum::operator=(bignum &&other) noexcept {
  if (&other != this) {
    value_ = std::move(other.value_);
    sign_ = other.sign_;
  }
  return *this;
}

const bignum bignum::operator++(int) {
  bignum current(*this);
  ++(*this);
  return current;
}

bignum &bignum::operator++() {
  if (!sign_ && value_.all())
    throw std::overflow_error("number is too big");

  if (value_.none())
    sign_ = false;
  if (sign_)
    --value_;
  else
    ++value_;
  return *this;
}

const bignum bignum::operator--(int) {
  bignum current(*this);
  --(*this);
  return current;
}

bignum &bignum::operator--() {
  if (sign_ && value_.all())
    throw std::underflow_error("number is too small");

  if (value_.none())
    sign_ = true;
  if (sign_)
    ++value_;
  else
    --value_;
  return *this;
}

bignum &bignum::operator+=(const bignum &added) {
  return sum(added, added.sign_ == sign_);
}

bignum &bignum::operator-=(const bignum &removed) {
  return sum(removed, removed.sign_ != sign_);
}

bignum &bignum::operator*=(const bignum &times) {
  value_ *= times.value_;

  join_sign(times.sign_);

  return *this;
}

bignum &bignum::operator/=(const bignum &divisor) {
  auto &divisor_value = divisor.value_;
  if (value_ < divisor_value)
    value_.reset();
  else
    value_ = std::move(divide(value_, divisor_value).first);

  join_sign(divisor.sign_);

  return *this;
}

bignum &bignum::operator%=(const bignum &divisor) {
  auto &divisor_value = divisor.value_;
  if (divisor_value.none() || divisor.sign_)
    throw std::invalid_argument("divisor is negative or 0");

  if (value_ < divisor_value)
    return *this;

  value_ = move(divide(value_, divisor_value).second);

  return *this;
}

bignum &bignum::power(unsigned short exponent) {
  if (sign_)
    sign_ = (exponent & 1U) == 1U;
  if (value_.any()) {
    std::bitset<sizeof(exponent) * 8> expon(exponent);

    bits_value result(0x01U);
    bits_value current(value_);

    unsigned char prev = 0;
    for (unsigned char i = prev; i < expon.size(); ++i) {
      if (expon.test(i)) {
        auto span = i - prev;
        prev = i;
        for (unsigned char j = 0; j < span; ++j)
          current *= current;
        result *= current;
      }
    }

    value_ = move(result);
  }
  return *this;
}

bignum bignum::mod_inverse_of(const bignum &mod) const {
  /*
  s[0] = 1, s[1] = 0
  t[0] = 0, t[1]= 1
  r[0] = a, r[1] = b.
  with mathematical induction:
  if
  r[i+1] = r[i-1] - r[i]*q
  s[i+1] = s[i-1] - s[i]*q
  t[i+1] = t[i-1] - t[i]*q
  r[i] = a*t[i] + b*s[i]
  then prove:
  r[i+1] = a*t[i+1] + b*s[i+1]
  until r[k] = 0, then t[k] or s[k] is the inverse module.
  */
  auto t = std::make_pair(bignum(0x00), bignum(0x01U));
  std::pair<bits_value, bits_value> r(mod.value_, value_);

  while (r.second.any()) {
    auto d = divide(r.first, r.second);
    r.first = r.second;
    r.second = d.second;

    // t.first = t.second, t.second = first - second*d.quotient
    auto transit = t.second;
    t.second *= bignum(move(d.first));
    t.first -= t.second;
    t.second = t.first;
    t.first = std::move(transit);
  }

  if (r.first.test(0) && r.first.count() == 1) {
    if (t.first.sign_)
      t.first.value_.reverse_substract(mod.value_);
    t.first.sign_ = sign_;

    return std::move(t.first);
  }

  throw coprime_error("given two nums are not co-prime");
}

size_t bignum::size() { return value_.size(); }

bignum &bignum::sum(const bignum &value, bool same_sign) {
  if (same_sign) {
    if (value_.check_adding_overflow(value.value_))
      throw std::overflow_error("number is too big");
    value_ += value.value_;
  } else {
    if (value_ == value.value_) {
      value_.reset();
      sign_ = false;
    } else if (value_ < value.value_) {
      sign_ = !sign_;
      value_.reverse_substract(value.value_);
    } else
      value_ -= value.value_;
  }

  return *this;
}

void bignum::join_sign(bool other_sign) {
  if (value_.none())
    sign_ = false;
  else
    sign_ ^= other_sign;
}

bool operator==(const bignum &left, const bignum &right) {
  return left.value_ == right.value_ && left.sign_ == right.sign_;
}

} // namespace arithmetic
