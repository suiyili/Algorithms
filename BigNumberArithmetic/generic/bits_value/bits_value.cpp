#include "bits_value.hpp"
#include "generic/coprime_error.hpp"

namespace generic {
bits_value::bits_value(const std::valarray<unsigned char> hex_value) {
  if (hex_value.size() * 8 > capacity)
    throw std::invalid_argument("overflow");

  for (size_t i = 0; i < hex_value.size(); ++i) {
    big_bits::operator<<=(8);
    big_bits::operator|=(hex_value[i]);
  }
}

bits_value::bits_value(const bits_value &other) noexcept : big_bits(other) {}

bits_value::bits_value(bits_value &&other) noexcept
    : big_bits(std::move(other)) {}

bits_value::bits_value(const big_bits &other) noexcept: big_bits(other) {}

bits_value::bits_value(big_bits &&other) noexcept: big_bits(other) {}

bits_value &bits_value::operator=(const bits_value &other) noexcept {
  if (this != &other) {
    big_bits::operator=(other);
  }
  return *this;
}

bits_value &bits_value::operator=(bits_value &&other) noexcept {
  if (this != &other) {
    big_bits::operator=(move(other));
  }
  return *this;
}

bits_value &bits_value::left_shift_within_limit(bits_size_t left_shift) {
  bits_size_t space_left = capacity - bits_span();
  if (space_left < left_shift)
    throw std::overflow_error("number is too big");
  big_bits::operator<<=(left_shift);
  return *this;
}

bits_size_t bits_value::bits_span() const {
  for (bits_size_t i = 0; i < capacity; ++i) {
    auto j = capacity - i - 1;
    if (big_bits::test(j))
      return j + 1;
  }
  return 0;
}

bits_value &bits_value::flip_until(bool bit_occur) {
  bits_size_t i = 0;

  for (; i < capacity && big_bits::test(i) != bit_occur; ++i)
    big_bits::set(i, bit_occur);
  if (i < capacity)
    big_bits::set(i, !bit_occur);

  return *this;
}

bool bits_value::check_adding_overflow(const bits_value &other) const {
  for (bits_size_t i = 0; i < capacity; ++i) {
    auto j = capacity - i - 1;
    // 1 & 0 is channel to pass 1&1 up to max
    // 0 & 0 will stop any channel pass
    if (!(big_bits::test(j) ^ other.test(j))) {
      return big_bits::test(j) & other.test(j);
    }
  }
  return false;
}

bits_value &bits_value::operator++() {
  flip_until(false);
  return *this;
}

bits_value &bits_value::operator--() {
  flip_until(true);
  return *this;
}

bits_value &bits_value::operator+=(const bits_value &other) {
  /* a & b get common, left shift 1 of common as new left
  a xor b get combine diff as new right
  new left and right goto first step
  */
  bits_value common_sum(other);
  do {
    auto common = *this & common_sum;
    *this ^= common_sum;
    common_sum = common << 1U;
  } while (common_sum.any());

  return *this;
}

bits_value &bits_value::operator-=(const bits_value &other) {
  /* x is the max(take all bits, 1111..11)
  so x + 1 = 0, closure domain
  x - b is b.flip
  so a - b = a - b + (x + 1) = a + (x - b) + 1
  */
  bits_value deducer(other);
  prepare_deducer(deducer);
  return *this += deducer;
}

bits_value &bits_value::reverse_substract(const bits_value &other) {
  prepare_deducer(*this);
  return *this += other;
}

bits_value &bits_value::operator*=(const bits_value &other) {
  /*one number do left shift according to if another is 1
  then sum all shifted numbers*/
  bits_value result;
  bits_value current(*this);

  bits_size_t prev = 0;

  for (decltype(prev) i = prev; i < capacity; ++i) {
    if (other.test(i)) {
      auto shift = i - prev;
      prev = i;
      current.left_shift_within_limit(shift);
      if (result.check_adding_overflow(current))
        throw std::overflow_error("number is too big");
      result += current;
    }
  }
  *this = move(result);
  return *this;
}

void bits_value::prepare_deducer(bits_value &deducer) {
  deducer.flip();
  ++deducer;
}

std::pair<bits_value, bits_value> divide(const bits_value &dividend,
                                         const bits_value &divisor) {
  /*from left to right, use divisor len as chunk
  substract divisor, if not enough,
  then left shift to add more data from dividend
  and to divided result
  and to carry on.
  */
  if (divisor.none())
    throw std::overflow_error("divisor is 0");

  bits_size_t cursor = dividend.bits_span() - divisor.bits_span();
  bits_value divided;
  bits_value remainder = dividend >> cursor;

  while (cursor > 0) {
    if (remainder < divisor) {
      divided <<= 1U;
      remainder <<= 1U;
      remainder.set(0, dividend.test(--cursor));
    } else {
      remainder -= divisor;
      divided.set(0);
    }
  }

  if (!(remainder < divisor)) {
    divided.set(0);
    remainder -= divisor;
  }

  return make_pair(move(divided), move(remainder));
}

bool operator<(const bits_value &left, const bits_value &right) {
  for (bits_size_t i = 0; i < capacity; ++i) {
    auto j = capacity - i - 1;
    auto right_bit = right.test(j);
    if (left.test(j) ^ right_bit)
      return right_bit;
  }
  return false;
}

} // namespace arithmetic
