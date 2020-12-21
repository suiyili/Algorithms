#pragma once

#include <bitset>

namespace algebra::generic {
class bit_analyzer final {
 public:
  bit_analyzer(size_t value);
  ~bit_analyzer() = default;

  void move_start();
  size_t move_next_true();

  size_t no_next_true() const;

 private:
  const std::bitset<sizeof(size_t) * 8U> value_;
  size_t cursor_, next_;
};

}