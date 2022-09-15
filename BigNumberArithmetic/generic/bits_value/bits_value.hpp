#pragma once

#include <bitset>
#include <utility>
#include <valarray>

namespace generic {
using bits_size_t = unsigned short;
constexpr bits_size_t capacity = 2048;
using big_bits = std::bitset<capacity>;

class bits_value final : public big_bits {
public:
  using big_bits::big_bits;
  bits_value() = default;
  bits_value(const std::valarray<unsigned char> hex_value);
  ~bits_value() = default;

  // it does inherit copy/move from parent
  // but those func signature is not this class copy/move signature

  bits_value(const bits_value &other) noexcept;
  bits_value(bits_value &&other) noexcept;

  bits_value(const big_bits &other) noexcept;
  bits_value(big_bits &&other) noexcept;

  bits_value &operator=(const bits_value &other) noexcept;
  bits_value &operator=(bits_value &&other) noexcept;

  bits_size_t bits_span() const;
  bool check_adding_overflow(const bits_value &other) const;

  bits_value &operator++();
  bits_value &operator--();
  bits_value &operator+=(const bits_value &other);
  bits_value &operator-=(const bits_value &other);
  bits_value &reverse_substract(const bits_value &other);
  bits_value &operator*=(const bits_value &other);
  friend std::pair<bits_value, bits_value> divide(const bits_value &dividend,
                                                  const bits_value &divisor);
  friend bool operator<(const bits_value &left, const bits_value &right);

private:
  static void prepare_deducer(bits_value &deducer);
  bits_value &flip_until(bool bit_occur);
  bits_value &left_shift_within_limit(bits_size_t left_shift);
};

} // namespace arithmetic
